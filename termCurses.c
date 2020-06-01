#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include <curses.h>

struct timespec *subtractTime(const struct timespec *t1, const struct timespec *t2) {
    if (t1 == NULL || t2 == NULL) return NULL;

    struct timespec *subd = malloc(sizeof(struct timespec));
    if (t1->tv_sec < t2->tv_sec) {
        subd->tv_sec = 0;
    } else {
        subd->tv_sec = t1->tv_sec - t2->tv_sec;
        if (t1->tv_nsec < t2->tv_nsec) {
            subd->tv_sec--;
            subd->tv_nsec = 1000000000UL - (t2->tv_nsec - t1->tv_nsec);
        } else {
            subd->tv_nsec = t1->tv_nsec - t2->tv_nsec;
        }
    }
    return subd;
}


typedef struct charS {
    int c_char;
    struct timespec c_time;
} charS;

charS *charS_create(int cChar) {
    charS *newC = malloc(sizeof(charS));
    newC->c_char = cChar;
    clock_gettime(CLOCK_REALTIME, &newC->c_time);
    return newC;
}

void charS_free(charS *c) {
    if (c == NULL) return;
    free(c);
}


#define NCHARS 40
charS *lastChars[NCHARS];
size_t ci = 0;

size_t get_ci() {
    return ci;
}

void inc_ci() {
    ci = (ci+1) % NCHARS;
}



int main(int argc, char *argv[]) {
    WINDOW *win = initscr();
    raw();
    keypad(win, TRUE);
    noecho();
    refresh();

    int max_x, max_y;
    getmaxyx(win, max_y, max_x);



    // INIT ARRAY
    for (size_t i = 0; i < NCHARS; ++i) {
        lastChars[i] = NULL;
    }


    int cChar;
    while ((cChar = getch()) != 'q') {
        // Set current char in barrel-queue
        if (lastChars[get_ci()] != NULL) {
            charS_free(lastChars[get_ci()]);
        }
        lastChars[get_ci()] = charS_create(cChar);

        // Print chars
        wmove(win, 1, 4);
        for (size_t i = NCHARS; i > 0; --i) {
            //mvprintw(1, 4, "ci + i: %d, i: %d , ci: %d", get_ci() + i, (get_ci() + i) % NCHARS, get_ci());
            //waddch(win, lastChars[i] == NULL ? ' ' : lastChars[i]->c_char);
            //clrtoeol();

            size_t cInd = (get_ci() + i) % NCHARS;
            waddch(win, lastChars[cInd] == NULL ? '_' : lastChars[cInd]->c_char);
        }
    
        mvprintw(2, 4, "You pressed: %c", cChar);
        clrtoeol();
        move(0,0);
        refresh();

        inc_ci();
    }
    
    endwin();
    for (size_t i = 0; i < NCHARS; ++i) {
        if (lastChars[i] != NULL) {
            charS_free(lastChars[i]);
        }
    }
    exit(EXIT_SUCCESS);
}
