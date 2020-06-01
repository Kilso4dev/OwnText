
#ifndef OWNTEXT_TERM_H
#define OWNTEXT_TERM_H

#include "prog.h"
#include "owntext.h"

void term_enable_raw();

void term_disable_raw();



unsigned char term_read_in();

void term_write_c(const char c);
void term_write_s(const char *s);
void term_write_int(const int i);

prog_dimension *term_get_dim();

void term_clear_screen();

int term_get_cursor_pos(int *line, int *offset);

int term_set_cursor_pos(const int line, const int offset);

int term_curs_right(int amount);
int term_curs_left(int amount);
int term_curs_up(int amount);
int term_curs_down(int amount);

int term_curs_sol();


int term_get_screen_dim(prog_dimension *term_dim);

#endif //OWNTEXT_TERM_H
