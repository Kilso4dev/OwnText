#include <stdarg.h>
#include <math.h>
#include "prog.h"
#include "termio.h"
#include "string.h"
#include "owntext.h"

ot_state editor_state;

#define TEXT_TOP_OFFSET 1
#define TEXT_BOTTOM_OFFSET 3
void prog_cleanup();

void prog_terminate(int code, const char *s) {
    //term_clear_screen();
    print_err(s);
    print_err("\n\r\t "/*Exiting with Code %d\n\r", code*/);
    //editor_state.main_running = 0;
    prog_cleanup();
    exit(code);
}

void print_err(const char *format, ...) {
    va_list vaList;
    va_start(vaList, format);
    fprintf(stderr, format, vaList);
    va_end(vaList);
}

void prog_init() {
    editor_state = (ot_state) {.term_dim = {1, 1},
            .window = {.cursor_line = 0, .cursor_offset = 0, .img_height = 1, .buffer = ot_buf_create_index(0)},
            .main_running = 1,
            .bufs = ot_buf_head_create(),
            .c_buf = 0
    };
    ot_buf_insert_buffer_after(editor_state.bufs, -1, ot_buf_create_index(0));
    term_enable_raw();

    term_clear_screen();
}

void prog_reprint_screen() {
    term_set_cursor_pos(0, 0);
    const int max_number_len = (int)log10((double)editor_state.bufs->length)+1;

    //int j = 0;

    ot_buffer *c_buf = editor_state.window.first_img_buffer;
    term_write_s("iterate to: ");
    term_write_int((TEXT_TOP_OFFSET + TEXT_BOTTOM_OFFSET) - editor_state.window.img_height);
    for (int i = 0; i < (TEXT_TOP_OFFSET + TEXT_BOTTOM_OFFSET) - editor_state.window.img_height ; i++) {
        if (c_buf != NULL && c_buf->next != NULL) {
            c_buf = c_buf->next;
            //TODO Print Numbers
            //term_set_cursor_pos(j++, 0);
            //printf("cPos: %d\n\r", i-c_buf->index);
            term_set_cursor_pos(i + TEXT_TOP_OFFSET, 0);

            term_write_s("  ");
            term_write_int(c_buf->index);

            for (int j = 0; j < max_number_len - log10((double) c_buf->index) + 1 ; ++j) {
                term_write_c(' ');
            }
        } else {
            term_set_cursor_pos(i + TEXT_TOP_OFFSET, 0);
            term_write_c('~');
        }
        //fsync(STDOUT_FILENO);
    }
    term_set_cursor_pos(0, ((int)log10((double)editor_state.term_dim.y))+1);
    for (int i = 0; i < editor_state.term_dim.y; i++) {

        term_set_cursor_pos(i, 0);
    }
}


//Cleanup and freeing of programs parameters and global structures when program ends TODO WIP
void prog_cleanup() {
    ot_buf_free(editor_state.bufs);
    //term_disable_raw();

}




/**  image utility  **/
/*
prog_image* prog_image_create(int columns, int rows) {
    prog_image *new_image = malloc(sizeof(prog_image));
    if (new_image != NULL)  {
        new_image->columns = columns;
        new_image->rows = rows;


        new_image->content = malloc((rows*columns) * sizeof(char));
        new_image->cursor_pos = prog_position_create();
        if (new_image->content == NULL || new_image->cursor_pos == NULL) {
            prog_terminate(31, "prog_image_create new_image:inner");
        } else {
            for (int i = 0; i < (columns * rows); ++i) {
                new_image->content[i] = ' ';
            }
        }

    } else prog_terminate(30, "prog_image_create");



    return new_image;
}

void prog_image_resize(prog_image *img, int new_columns, int new_rows) {
    if (img != NULL) {
        img->columns = new_columns;
        img->rows = new_rows;
        if (img->content != NULL) {
            img->content = realloc(img->content, sizeof(char) * (new_columns * new_rows));
        } else {
            img->content = malloc(new_columns*new_rows * sizeof(char));
        }
        for (int i = 0; i < (new_columns * new_rows); ++i) {
            img->content[i] = ' ';
        }
    }
}

void prog_image_free(prog_image *image) {
    if (image != NULL) {
        if (image->content != NULL) free(image->content);
        if (image->cursor_pos != NULL) prog_position_free(image->cursor_pos);
        free(image);
    }
}

unsigned char get_char_i(prog_image* ref_img, int i) {
    if (i < 0 || i >= (ref_img->rows*ref_img->columns)) {
        return 0;
    } else {
        return (ref_img->content)[i];
    }
}

unsigned char get_char_coords(prog_image* ref_img, prog_position *pos) {
    return get_char_i(ref_img, i_from_position(ref_img, pos));
}

void set_char_i(prog_image* ref_img, int i, unsigned char c) {
    if (i < 0 || i >= (ref_img->rows*ref_img->columns)) {
        return;
    } else {
        ref_img->content[i] = c;
    }
}

void set_char_coords(prog_image* ref_img, prog_position *pos, unsigned char c) {
    return set_char_i(ref_img, i_from_position(ref_img, pos), c);
}
*/

/**  position utility  **/

prog_position * prog_position_create_by_pos(int column, int row) {
    prog_position *new_pos = malloc(sizeof(prog_position));
    if (new_pos != NULL) {
        new_pos->column = column;
        new_pos->row = row;
        return new_pos;
    } else return NULL;
}
prog_position * prog_position_create() {
    return prog_position_create_by_pos(0, 0);
}

void prog_position_free(prog_position *pos) {
    if (pos != NULL) {
        free(pos);
    }
}
/*
prog_position *position_from_i(const prog_image *ref_image, const int i) {
    if (i >= (ref_image->columns*ref_image->rows) || i<0) {
        prog_terminate(40, "position_from_i");
    }
    prog_position *pos = prog_position_create();
    pos->row = i/ref_image->columns;
    pos->column = i%ref_image->columns;
    return pos;
}

int i_from_position(const prog_image *ref_image, const prog_position *pos) {
    if (pos->column>=ref_image->columns  || pos->row>=ref_image->rows ||
        pos->column<0                  || pos->row<0) {
        prog_terminate(41, "i_from_position");
    }
    return (pos->row * ref_image->columns) + pos->column;
}
*/

/**  dimension util  **/

prog_dimension* prog_dimension_create_by_dim(const int columns, const int rows) {
    prog_dimension *new_dim = malloc(sizeof(prog_dimension));
    if (new_dim != NULL) {
        new_dim->x = columns;
        new_dim->y = rows;
        return new_dim;
    }
    return NULL;
}
prog_dimension* prog_dimension_create() {
    return prog_dimension_create_by_dim(0, 0);
}

void prog_dimension_free(prog_dimension *dim) {
    if (dim != NULL) {
        free(dim);
    }
}