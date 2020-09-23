#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "logging.h"
#include "args.h"
#include "window.h"


#define MAX_CYCLES 100

typedef struct owntext_state {
    edit_state *window_state;
    
    bool exit;
} owntext_state;

owntext_state editor_state = {.window_state = NULL, .exit = false};

int owntext_run();
int owntext_processInput();
int prog_init(int argc, char *argv[]);

void prog_cleanup() {

}

void prog_terminate(int code, const char *s) {
    logm(DEBUG_ERROR, s);
    //editor_state.main_running = 0;
    //prog_cleanup();
    exit(code);
}


/**  initialization  **/
int main(int argc, char *argv[]) {

    if (prog_init(argc, argv)) {
        prog_terminate(1, "Error while initialization");
    }

    if (owntext_run()) {
        prog_terminate(2, "Runtime Error");
    }

    exit(0);
}


int prog_init(int argc, char *argv[]) {
    logm(DEBUG_INFO, "Initialization!");
    
    editor_state.window_state = edit_init();
    logm(DEBUG_INFO, "")
    atexit(prog_cleanup);
    editor_state.exit = false;
    args *a = args_parse(argc, argv);

    return 0;
}

int owntext_run() {
    logm(DEBUG_INFO, "Running!");
    while (!editor_state.exit) {
        
    }
    /*int cycles = 0;
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
    }*/
    return 0;
}

int owntext_processInput() {
/*    char c = term_read_in();


    switch(c) {

        case CTRL_KEY('q'):
            prog_terminate(0, "");
            break;
        case 'c':
            term_clear_screen();
            break;
    }*/
    return 0;
}

