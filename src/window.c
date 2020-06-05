#include <curses.h>
#include "window.h"
#include "stdbool.h"

edit_state *edit_init() {
    edit_state *new_t_state = malloc(sizeof(edit_state));
    new_t_state->main_win = edit_win_create(initscr());
    
    raw();
    keypad(new_t_state->main_win->win, TRUE);
    noecho();
    refresh();

    return new_t_state;
}

void edit_state_free(edit_state **state) {
    if (state == NULL || *state == NULL) return;
    if ((*state)->main_win != NULL) {
        edit_win_free(&(*state)->main_win);
    }
    free(*state);
    *state = NULL;
}

edit_win *edit_win_create(WINDOW *newWin) {
    edit_win *new_edit_win = malloc(sizeof(edit_win));
    
    new_edit_win->sub_win_length = 0;
    new_edit_win->sub_wins = malloc(0);

    // Update screen struct (i.e. max_x/y) for the first time
    edit_win_update(new_edit_win);

    return new_edit_win;
}

void edit_win_free(edit_win **win) {
    if (win == NULL || *win == NULL) return;
    delwin((*win)->win);
    if ((*win)->sub_wins) {
        edit_win **subwins = (*win)->sub_wins;
        for (size_t i = 0; i < (*win)->sub_win_length; ++i) {
            edit_win_free(&(subwins[i]));
        }
        free((*win)->sub_wins);
        (*win)->sub_wins = NULL;
    }
    free(*win);
    *win = NULL;
}


void edit_win_update(edit_win *win) {
    if (win == NULL) return;
    
    // Recursive updates first
    if (win->sub_wins) {
        for (size_t i = 0; i < win->sub_win_length; ++i) {
            edit_win_update(win->sub_wins[i]);
        }
    }
    
    // Actual update
    getmaxyx(win->win, win->max_y, win->max_x);
}

