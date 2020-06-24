#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "../src/logging.h"
#include "../src/buf.h"

#define STR_SIZE 512

int main(int argc, char *args[]) {
    logm(DEBUG_WARNING, "Test Buffer");
    ot_buf *b = ot_buf_create_empty();
    
    char *cline = calloc(STR_SIZE, sizeof(char));
    for(size_t i = 0; i < 50; ++i) {
        if (snprintf(cline, STR_SIZE, "Line %ld", i) == 0) {
            continue;
        }
        ot_buf_line *newL = ot_buf_line_create((int *) cline);
        ot_buf_insert_after(b, newL, i < 1 ? 0 : i-1);
    }
    free(cline);

    ot_buf_print(b);

    ot_buf_free(b);

}
