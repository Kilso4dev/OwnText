#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>

// Sub

typedef struct edit_win {
    // Terminal window
    WINDOW *win;
    size_t max_y, max_x;

    //window information like cursor position
    //edit_view_data *view;
    
    // Subwindow management
    struct edit_win **sub_wins;
    size_t sub_win_length;
} edit_win;

typedef struct edit_state {
    edit_win *main_win;
} edit_state;



edit_state *edit_init();

void edit_state_free(edit_state **state);


edit_win *edit_win_create(WINDOW *newWin);

void edit_win_free(edit_win **win);


void edit_win_update(edit_win *win);
