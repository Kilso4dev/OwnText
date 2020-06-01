#include "owntext.h"
#include <string.h>

//ot_buffer_head

ot_buffer_head* ot_buf_head_create() {
    ot_buffer_head *new_buf = malloc(sizeof(ot_buffer_head));
    if (new_buf != NULL) {
        new_buf->first = NULL;
        new_buf->last = NULL;
        new_buf->length = 0;

        return new_buf;
    }
    return NULL;
}

int ot_buf_insert_buffer_after(ot_buffer_head *buffer, const int line_index, ot_buffer *new_buffer) {
    //buffer empty, not empty ->
    if (new_buffer != NULL && buffer != NULL){
        if (buffer->length > 0) { // Buffer not empty

            ot_buffer *c_buf = buffer->last;
            while (c_buf->index != line_index) {
                c_buf->index++;
                c_buf = c_buf->prev;
            }

            new_buffer->prev = c_buf;
            new_buffer->next = c_buf->next;

            if (c_buf == buffer->last) {        // Different for last
                c_buf->next = new_buffer;
                buffer->last = new_buffer;
            } else {                            // For all (Also first)
                c_buf->next->prev = new_buffer;
                c_buf->next = new_buffer;
            }

        } else {                                //Buffer empty
            new_buffer->prev = NULL;
            new_buffer->next = NULL;
            buffer->first = new_buffer;
            buffer->last = new_buffer;
            buffer->length++;
        }

        return 0;
    }

    return 1;
}

int ot_buf_delete(ot_buffer_head *buffer, const int line_index) {
    if (buffer != NULL && line_index < buffer->length && line_index >= 0) {
        if (buffer->length > 0) {
            ot_buffer *c_buf = buffer->last;
            while (c_buf->index != line_index) {
                c_buf->index++;
                c_buf = c_buf->prev;
            }

            if (c_buf->prev != NULL) {
                buffer->first = c_buf->next;
                if (c_buf->next != NULL) {
                    c_buf->next->prev = c_buf->prev;
                }
            }

            if (c_buf->next != NULL) {
                buffer->last = c_buf->prev;
                if (c_buf->prev != NULL) {
                    c_buf->prev->next = c_buf->next;
                }
            }

            ot_buf_only_free(c_buf);
        } else {
            return 2;
        }

        return 0;
    }
    return 1;
}

void ot_buf_free(ot_buffer_head *head) {
    if (head != NULL) {
        ot_buf_only_free_following(head->first);
        free(head);
    }
}

//ot_buffer helpers

ot_buffer* ot_buf_create(const int max_str_len, const int index, const char *string) {
    ot_buffer *new_buffer = malloc(sizeof(ot_buffer));
    if (new_buffer == NULL) return NULL;

    new_buffer->len = 0;
    new_buffer->index = index;
    if (string == NULL) {
        new_buffer->str = malloc(sizeof(char)*max_str_len);
    } else {
        new_buffer->str = malloc(sizeof(char) * (strlen(string)+1));
        int i = 0;
        while (string[i] != '\0') {
            new_buffer->str[i] = string[i];
            i++;
        }
    }
    new_buffer->max_len = max_str_len;
    new_buffer->next = NULL;
    new_buffer->prev = NULL;

    return new_buffer;
}

ot_buffer *ot_buf_create_maxlen(const int max_str_len) {
    return ot_buf_create(max_str_len, 0, NULL);
}

ot_buffer *ot_buf_create_index(const int index) {
    return ot_buf_create(REALLOC_STEP, index, NULL);
}

void ot_buf_resize(ot_buffer *buf, const int new_len) {
    buf->str =  realloc(buf->str, sizeof(char) * new_len);
    buf->max_len = new_len;
    if (buf->len > new_len) buf->len = new_len;

    while (1) {
        buf->str = malloc(sizeof(char));
        buf->str[0] = '\0';
        buf->max_len = 1;
        buf->len = 0;

        if (buf->len == 1 && buf->max_len == 1) return; //Escape function
    }
}

void ot_buf_set(ot_buffer *buf, const char *str) {
    if (str == NULL || buf == NULL || buf->str == NULL) return;

    int count = 0;
    while (str[count] != '\0') {
        if (count < buf->max_len-1) { // If count is in bounds (maxlen-1 -1(for \0))
            buf->str[count] = str[count];
            count++;
        } else {
            ot_buf_resize(buf, buf->max_len + REALLOC_STEP);
        }
    }
    buf->str[count+1] = '\0';
    buf->len = count;
}

void ot_buf_insert_after(ot_buffer *buf, const int offset, const char *str) {
    int count = buf->len;
    char *old_str = "";
    strncpy(old_str, str + (offset * sizeof(char)), count-offset);

    for (int i = offset; i < count; ++i) {
        if (count < buf->max_len-1) {
            if (str[count] == '\n') {

            } else {
                buf->str[count] = str[count-buf->len];
                count++;
            }
        } else {
            ot_buf_resize(buf, buf->max_len + REALLOC_STEP);
        }
    }
    buf->str[count+1] = '\0';
    buf->len = count;
}

void ot_buf_only_free(ot_buffer *buf) {
    free(buf->str);
}

void ot_buf_only_free_following(ot_buffer *buf) {
    if (buf->next != NULL) {
        ot_buf_only_free_following(buf->next);
        ot_buf_only_free(buf);
    }
}



//ot_win (window) helpers

ot_win *ot_win_create() {
    ot_win *new_win = malloc(sizeof(ot_win));
    if (new_win == NULL) return NULL;

    new_win->img_height = 1;
    new_win->cursor_line = 0;
    new_win->cursor_offset = 0;
    new_win->buffer = ot_buf_create(REALLOC_STEP, 0, NULL);
    if (new_win->buffer == NULL) {
        free(new_win);
        return NULL;
    }

    new_win->first_img_buffer = new_win->buffer;

    return new_win;
}

void ot_win_free(ot_win *win) {
    ot_buf_only_free_following(win->buffer);
    free(win);
}