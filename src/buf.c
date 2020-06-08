#include "buf.h"

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

ot_buf_line *ot_buf_line_create(const ot_char *str, ot_size line) {
    ot_buf_line *new_l = (ot_buf_line *) malloc(sizeof(ot_buf_line *));
    if (!new_l) {
        logm(DEBUG_ERROR, "[ot_buf_line] [create]: Error while allocating Memory");
        return NULL;
    }
    new_l->chars = ot_str_copy(str, ot_str_len(str)+1);
    new_l->line = line;
    
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
    new_buf->lastUsed = NULL;
    new_buf->lastUsedLine = 0;

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
        uint64_t target_line) {

}

void ot_buf_insert_before(
        ot_buf *head_buf,
        ot_buf_line *newLine,
        uint64_t target_line) {

}
