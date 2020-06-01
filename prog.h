#ifndef OWNTEXT_PROG_H
#define OWNTEXT_PROG_H

#define CTRL_KEY(k) ((k) & 0x1f)

typedef struct prog_position_s {
    int column, row;
} prog_position;


typedef struct prog_dimension_s {
    int x, y;
} prog_dimension;

/*typedef struct prog_l_image_s {
    unsigned int columns, rows;
    char *content;
    prog_position *cursor_pos;
} prog_image;
*/
void prog_terminate(int code, const char *s);

void print_err(const char *format, ...);

void prog_init();

void prog_reprint_screen();





/**  image util  **/
/*
prog_image* prog_image_create(int columns, int rows);

void prog_image_resize(prog_image *img, int new_columns, int new_rows);

void prog_image_free(prog_image *image);


unsigned char get_char_i(prog_image* ref_img, int i);

unsigned char get_char_coords(prog_image* ref_img, prog_position *pos);

void set_char_i(prog_image* ref_img, int i,unsigned char c);

void set_char_coords(prog_image* ref_img, prog_position *pos,unsigned char c);
*/





/**  position util  **/

prog_position* prog_position_create_by_pos(int column, int row);
prog_position* prog_position_create();

void prog_position_free(prog_position *pos);
/*
prog_position *position_from_i(const prog_image *ref_image, int i);

int i_from_position(const prog_image *ref_image, const prog_position *pos);
*/



/**  dimension util  **/

prog_dimension* prog_dimension_create_by_dim(int columns, int rows);
prog_dimension* prog_dimension_create();

void prog_dimension_free(prog_dimension *dim);

#endif //OWNTEXT_PROG_H
