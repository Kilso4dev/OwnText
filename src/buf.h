#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "logging.h"

#ifndef BUF_H
#define BUF_H

#define OT_BUF_LINE_REC_FREE_NONE 0
#define OT_BUF_LINE_REC_FREE_FORWARD 1
#define OT_BUF_LINE_REC_FREE_BACKWARD 2


#define ot_size uint64_t
#define ot_char int

// -------------------------string helper functions -------------------------
ot_size ot_str_len(ot_char *str);

ot_char *ot_str_copy(ot_char *old, ot_size len);

void ot_str_free(ot_char *str);

// -------------------------ot_buf_line functions -------------------------

typedef struct ot_buf_line {
    ot_char *chars;

    struct ot_buf_line *next;
    struct ot_buf_line *prev;
    
} ot_buf_line;


ot_buf_line *ot_buf_line_create(ot_char *str);

void ot_buf_line_free(ot_buf_line *l, int free_type);

// -------------------------ot_buf functions -------------------------

typedef struct ot_buf {
     ot_buf_line *first_line;
     ot_buf_line *last_line;
     
     uint64_t lines;

     ot_buf_line *last_used;
     uint64_t last_used_line;
} ot_buf;


ot_buf *ot_buf_create_empty();


void ot_buf_free(ot_buf *buf);


void ot_buf_insert_after(ot_buf *head_buf, ot_buf_line *newLine, uint64_t target_line);

void ot_buf_insert_before(ot_buf *head_buf, ot_buf_line *newLine, uint64_t target_line);

// ------------------------- utility functions -------------------------

void ot_buf_print(ot_buf *b);


#endif //BUF_H
