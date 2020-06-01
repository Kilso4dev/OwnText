#ifndef OWNTEXT_OWNTEXT_H
#define OWNTEXT_OWNTEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <termios.h>
#include <ctype.h>
#include <errno.h>
#include "Texts.h"
#include "prog.h"

#define REALLOC_STEP 128

typedef struct ot_buffer_s {
    struct ot_buffer_s *next;
    struct ot_buffer_s *prev;

    char *str;
    int len;
    int max_len;
    int index;
} ot_buffer;

typedef struct ot_buffer_head_s {
    ot_buffer *first;
    ot_buffer *last;
    int length;
} ot_buffer_head;


/*
 * Container of text buffer containing info about buffer itself, image height, cursor/mark position
 */
typedef struct ot_win_s {
    ot_buffer *buffer;

    ot_buffer *first_img_buffer;      //first buffer line of current image
    int img_height;
    int cursor_line;
    int cursor_offset;

} ot_win;

typedef struct ot_state_s {
    struct termios old_state;
    ot_win window;
    ot_buffer_head *bufs;
    int c_buf;
    int main_running;
    prog_dimension term_dim;
} ot_state;


extern ot_state editor_state;

//Helpers for buf head

ot_buffer_head* ot_buf_head_create();

int ot_buf_insert_buffer_after(ot_buffer_head *buffer, const int line_index, ot_buffer *new_buffer);

int ot_buf_delete(ot_buffer_head *buffer, const int line_index);


void ot_buf_free(ot_buffer_head *head);


//Helpers for buf

ot_buffer* ot_buf_create(const int max_str_len, const int index, const char *string);

ot_buffer *ot_buf_create_maxlen(const int max_str_len);

ot_buffer *ot_buf_create_index(const int index);

void ot_buf_resize(ot_buffer *buf, const int new_len);

void ot_buf_set(ot_buffer *buf, const char *str);

void ot_buf_insert_after(ot_buffer *buf, const int offset, const char *str);

void ot_buf_only_free(ot_buffer *buf);

void ot_buf_only_free_following(ot_buffer *buf);


// Helpers for window

ot_win *ot_win_create();

void ot_win_free(ot_win *win);

#endif //OWNTEXT_OWNTEXT_H
