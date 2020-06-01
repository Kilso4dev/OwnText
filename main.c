#include "owntext.h"
#include "prog.h"
#include "termio.h"

#define MAX_CYCLES 100

void owntext_run();
void owntext_processInput();



/**  initialization  **/
int main(int argc, char *args[]) {
    prog_init();

    owntext_run();

    prog_terminate(0, "");
    return 0;
}


void owntext_run() {
    int cycles = 0;
    while (editor_state.main_running) {
        //str TODO apend cycles count to String

        //term_set_cursor_pos(0, 0);
        if (cycles%20 == 0) {
            term_get_screen_dim(&editor_state.term_dim);
        }
        owntext_processInput();
        term_get_cursor_pos(&editor_state.window.cursor_line, &editor_state.window.cursor_offset);

        prog_reprint_screen();

        //Cycles
        cycles++;
        if (cycles >= MAX_CYCLES) {
            cycles = 0;
        }
    }
}

void owntext_processInput() {
    char c = term_read_in();


    switch(c) {

        case CTRL_KEY('q'):
            prog_terminate(0, "");
            break;
        case 'c':
            term_clear_screen();
            break;
    }
}