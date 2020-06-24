#include "buf.h"

#define OT_DIR_FORWARD 2
#define OT_DIR_BACKWARD 4

ot_buf_line *ot_buf_get_nearestpointer(
        ot_buf *b,
        ot_size tl, 
        int *dir,
        ot_size *n_line) {
    if (tl >= b->lines) {
        logm(DEBUG_ERROR, "[ot_buf_get_nearestpointer] target Line is bigger than buffer Lines, returning NULL");
        return NULL;
    }
    

    if (tl <= b->last_used_line) { // sl - »tl - ll - el
        if (tl <= (b->last_used_line/ 2)) { // Closer to the first line
            if (dir) *dir = OT_DIR_FORWARD;
            if (n_line) *n_line = 0;
            return b->first_line;
        } else { // Closer to the last used line
            if (dir) *dir = OT_DIR_BACKWARD;
            if (n_line) *n_line = b->last_used_line;
            return b->last_used;
        }
    } else { // sl - ll - »tl - el
        if (tl <= ( b->last_used_line + ((b->lines - 1 - b->last_used_line) / 2))) { // Closer to the last used line
            if (dir) *dir = OT_DIR_FORWARD;
            if (n_line) *n_line = b->last_used_line;
            return b->last_used;
        } else { // Closer to the last line
            if (dir) *dir = OT_DIR_BACKWARD;
            if (n_line) *n_line = b->lines-1;
            return b->last_line;
        }
    }
}

ot_buf_line *ot_find_buf(
        ot_buf *head_buf,
        ot_size target_line) {
    if (!head_buf) return NULL;

    int readDirection = 0;
    ot_size n_line = 0;
    ot_buf_line *n_buf = ot_buf_get_nearestpointer(
            head_buf, 
            target_line, 
            &readDirection,
            &n_line);
    if (!n_buf) { 
        // current buffer state (i.e. empty) config is not valid for better buf position finding: ignoring
        n_buf = head_buf->first_line;
    }

    ot_size c_buf_l = n_line;
    ot_buf_line *c_buf = n_buf;
    while ( c_buf_l != target_line)  {
        if (readDirection == OT_DIR_BACKWARD) {
            if (!c_buf->prev) return c_buf;
            c_buf = c_buf->prev;
            c_buf_l -= 1;
        } else {
            if (!c_buf->next) return c_buf;
            c_buf = c_buf->next;
            c_buf_l += 1;
        }
    }
    return c_buf;
}


// -------------------------string helper functions -------------------------
ot_size ot_str_len(ot_char *str) {
    ot_size i = 0;
    while (str[i] != '\0') {
        ++i;
    }
    return i;
}

ot_char *ot_str_copy(ot_char *old, ot_size len) {
    ot_char *new_str = (ot_char *) malloc(sizeof(ot_char) * len);
    if (!new_str) return NULL;
    for (ot_size i = 0; i < len && old[i] != '\0'; ++i) {
        new_str[i] = old[i];
    }
    return new_str;
}

void ot_str_free(ot_char *str) {
    if (!str) return;
    free(str);
}

// -------------------------ot_buf_line functions -------------------------

ot_buf_line *ot_buf_line_create(ot_char *str) {
    ot_buf_line *new_l = (ot_buf_line *) malloc(sizeof(ot_buf_line));
    if (!new_l) {
        logm(DEBUG_ERROR, "[ot_buf_line] [create]: Error while allocating Memory");
        return NULL;
    }
    new_l->chars = ot_str_copy(str, ot_str_len(str)+1);
    
    new_l->next = NULL;
    new_l->prev = NULL;


    return new_l;
}

void ot_buf_line_free(ot_buf_line *l, int free_type) {
    if (!l) return;
    
    ot_str_free(l->chars);

    switch (free_type) {
        case OT_BUF_LINE_REC_FREE_FORWARD: 
            {
                ot_buf_line_free(l->next, OT_BUF_LINE_REC_FREE_FORWARD);
                break;
            }
        case OT_BUF_LINE_REC_FREE_BACKWARD:
            {
                ot_buf_line_free(l->prev, OT_BUF_LINE_REC_FREE_BACKWARD);
                break;
            }
    }
    free(l);
}

// -------------------------ot_buf functions -------------------------

ot_buf *ot_buf_create_empty() {
    ot_buf *new_buf = (ot_buf *) malloc(sizeof(ot_buf));
    if (!new_buf) {
        logm(DEBUG_ERROR, "[ot_buf] [create_empty]: Error while allocating Memory");
        return NULL;
    }

    new_buf->first_line = NULL;
    new_buf->last_line = NULL;
    new_buf->last_used= NULL;
    new_buf->last_used_line = 0;

    new_buf->lines = 0;

    return new_buf;
}

void ot_buf_free(ot_buf *buf) {
    if (!buf) return;

    ot_buf_line_free(buf->first_line, OT_BUF_LINE_REC_FREE_FORWARD);

    free(buf);
}

void ot_buf_insert_after(
        ot_buf *head_buf,
        ot_buf_line *newLine,
        ot_size target_line) {

    if (!head_buf->first_line && !head_buf->last_line) { 
        // Uninitialized Head, this is the first item
        head_buf->first_line = newLine;
        head_buf->last_line = newLine;
        head_buf->last_used = newLine;
        head_buf->last_used_line = 0;
        head_buf->lines = 1;
        return;
    }

    ot_buf_line *target_buf = ot_find_buf(head_buf, target_line);
    ot_buf_line *next_buf = target_buf->next;

    target_buf->next = newLine;
    newLine->next = next_buf;

    if (next_buf) next_buf->prev = newLine;
    newLine->prev = target_buf;

    if (!next_buf) head_buf->last_line = newLine;
 
    // Update last used
    head_buf->last_used = newLine;
    head_buf->last_used_line = target_line + 1;

    // Update lines
    head_buf->lines += 1;
}

void ot_buf_insert_before(
        ot_buf *head_buf,
        ot_buf_line *newLine,
        ot_size target_line) {
    if (!head_buf->first_line && !head_buf->last_line) { // Uninitialized
        ot_buf_insert_after(
                head_buf,
                newLine,
                target_line);
        return;
    }

    ot_buf_line *target_buf = ot_find_buf(head_buf, target_line);
    ot_buf_line *prev_buf = target_buf->prev;

    target_buf->prev = newLine;
    newLine->prev = prev_buf;

    if (prev_buf) prev_buf->next = newLine;
    newLine->next = target_buf;

    if (!prev_buf) head_buf->first_line = newLine;

    // Update last used
    head_buf->last_used = newLine;
    head_buf->last_used_line = target_line;

    // Update lines
    head_buf->lines += 1;
}


// ------------------------- utility functions -------------------------

void ot_buf_print(ot_buf *b) {
    debug_lvl L = DEBUG_INFO;
    if (!b) {
        logm(L, "NULL");
        return;
    }

    if (!b->first_line) {
        logm(L, "First Line is NULL");
        return;
    }
    
    ot_buf_line *cLine = b->first_line;
    ot_size cli = 1;
    while (cLine) {
        logm(L, " Line %ld", cli);
        logm(L, "\t Prev: %p", cLine->prev);
        logm(L, "\t Self: %p", cLine);
        logm(L, "\t Next: %p", cLine->next);
        logm(L, "\t Content: \"%s\"\n", cLine->chars);

        cLine = cLine->next;
        ++cli;
    }

}
