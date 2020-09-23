#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "logging.h"
#include "config.h"

#ifndef BUF_H
#define BUF_H

#define OT_BUF_LINE_REC_FREE_NONE 0
#define OT_BUF_LINE_REC_FREE_FORWARD 1
#define OT_BUF_LINE_REC_FREE_BACKWARD 2



// -------------------------string helper functions -------------------------
uint64_t ot_str_len(int *str);

int *ot_str_copy(int *old, uint64_t len);

void ot_str_free(int *str);

// -------------------------ot_buf_line functions -------------------------

typedef struct ot_buf_line {
    int *chars;

    struct ot_buf_line *next;
    struct ot_buf_line *prev;
    
} ot_buf_line;


ot_buf_line *ot_buf_line_create(int *str);

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


int ot_buf_insert_after(ot_buf *head_buf, ot_buf_line *newLine, uint64_t target_line);

int ot_buf_insert_before(ot_buf *head_buf, ot_buf_line *newLine, uint64_t target_line);

void ot_buf_delete_target(ot_buf *head_buf, ot_buf_line *target_line);

void ot_buf_delete_line(ot_buf *head_buf, uint64_t target_line);

// ------------------------- utility functions -------------------------

void ot_buf_print(ot_buf *b);


#endif //BUF_H
