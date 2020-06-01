#include <string.h>
#include <sys/ioctl.h>
#include <math.h>

#include "termio.h"
#include "owntext.h"
#include "prog.h"

#define SHORT_BUF_LEN 16

int term_get_screen_dim_legacy(prog_dimension *term_dim);
void term_set_flags(struct termios *raw);
void term_reset_flags();


int term_set_raw_cursor_pos(const prog_position *pos);

/**  Term Setup  **/
void term_enable_raw() {
    if (tcgetattr(STDIN_FILENO, &editor_state.old_state) == -1) {
        prog_terminate(2, "enableRaw: (tcgetAttr)");
    }
    atexit(&term_disable_raw);

    struct termios raw = editor_state.old_state;
    term_set_flags(&raw);

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        prog_terminate(2, "enableRaw: (tcsetAttr)");
    }
}
void term_disable_raw() {
    term_reset_flags();
}
void term_reset_flags() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &editor_state.old_state) == -1) {
        prog_terminate(3, "disableRaw: term_reset_flags: (tcsetAttr)");
    }
}
void term_set_flags(struct termios *raw) {
    raw->c_iflag &= ~(BRKINT | ICRNL | ICRNL | IXON);
    raw->c_oflag &= ~(OPOST);
    raw->c_cflag |= (CS8);
    raw->c_lflag &= ~(ECHO | ICANON | IEXTEN /*| ISIG*/);

    raw->c_cc[VMIN] = 0;
    raw->c_cc[VTIME] = 1;
}


/**  Term Input Utility  **/

/**  LOW Level functions  **/
unsigned char term_read_in() {
    int code = 0, c = '\0';
    while ((code = read(STDIN_FILENO, &c, 1)) == -1) {
        if (code == -1 && errno != EAGAIN) {
            return 0;
        }
    }

    return c;
}
void term_write_c(const char c) {
    char str[2] = {c, '\0'};
    if (write(STDOUT_FILENO, str, 1) != 1) {
        print_err("Could not write to output, ignoring");
    }
}

void term_write_s(const char *s) {
    int sLen = strlen(s);
    if (write(STDOUT_FILENO, s, sLen) != sLen) {
        print_err("Could not write to output, ignoring");
    }
}

void term_write_int(const int i) {


    int s_len = (int)log10(i)+2;
    char *s = malloc(s_len * sizeof(char));
    snprintf(s, s_len, "%d", i);
    if (s == NULL || write(STDOUT_FILENO, s, s_len-1) != s_len-1) {
        print_err("Could not write Integer to Terminal");
    }
    free(s);
}

prog_dimension *term_get_dim() {
    return &editor_state.term_dim;
}



/**  HIGH Level functions  **/

void term_clear_screen() {
    write(STDOUT_FILENO, "\033[2J", 4);
    write(STDOUT_FILENO, "\033[H", 3);
}

int term_get_cursor_pos(int *line, int *offset) {
    int buf_len = 32;
    char buf[buf_len];
    unsigned int i = 0;

    if (write(STDOUT_FILENO, "\033[6n", 4) != 4) return -1;
    while (i < buf_len) {
        if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
        if (buf[i] == 'R') break;
        i++;
    }

    buf[i] = '\0';
    if (buf[0] != '\033' || buf[1] != '[') return -1;
    if (sscanf(&buf[2], "%d;%d", line, offset) != 2) return -1;
    return 0;
}

int term_set_cursor_pos(const int line, const int offset) {
    int buf_len = 16;
    char str[buf_len]; str[0] = '\0';
    snprintf(str, buf_len, "\033[%d;%dH", line, offset);
    write(STDOUT_FILENO, str, strlen(str));

    editor_state.window.cursor_line = line;
    editor_state.window.cursor_offset = offset;

    return 0;
}

int term_curs_right(int amount) {
    char str[SHORT_BUF_LEN]; str[0] = '\0';
    snprintf(str, SHORT_BUF_LEN, "\033[%dC", amount);
    return write(STDOUT_FILENO, str, strlen(str));
}
int term_curs_left(int amount) {
    char str[SHORT_BUF_LEN]; str[0] = '\0';
    snprintf(str, SHORT_BUF_LEN, "\033[%dD", amount);
    return write(STDOUT_FILENO, str, strlen(str));
}
int term_curs_up(int amount) {
    char str[SHORT_BUF_LEN]; str[0] = '\0';
    snprintf(str, SHORT_BUF_LEN, "\033[%dA", amount);
    return write(STDOUT_FILENO, str, strlen(str));
}
int term_curs_down(int amount) {
    char str[SHORT_BUF_LEN]; str[0] = '\0';
    snprintf(str, SHORT_BUF_LEN, "\033[%dB", amount);
    return write(STDOUT_FILENO, str, strlen(str));
}

int term_curs_sol() {
    return write(STDOUT_FILENO, "\033[0E", 4);
}


int term_get_screen_dim(prog_dimension *term_dim) {
    struct winsize new_ws;
    term_dim->x = 30;
    term_dim->y = 10;
    return 0;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &new_ws) == -1 || new_ws.ws_col == 0) {
        return term_get_screen_dim_legacy(term_dim);
    } else if ((term_dim->x != new_ws.ws_col && term_dim->y != new_ws.ws_row)) {
        term_dim->x = new_ws.ws_col;
        term_dim->y = new_ws.ws_row;
        return 0;
    }
    return 1;
}

int term_get_screen_dim_legacy(prog_dimension *term_dim) {
    int old_line, old_offs;
    term_get_cursor_pos(&old_line, &old_offs);

    prog_position *curs_pos = prog_position_create();
    if (write(STDOUT_FILENO, "\033[9999C\033[9999B", 14) != 14) return -1; //legacy way (assuming not more than 1000 Columns/Rows possible in Terminal)
    int ret = term_get_cursor_pos(&(curs_pos->row), &(curs_pos->column));

    term_dim->x = curs_pos->column;
    term_dim->y = curs_pos->row;

    term_set_cursor_pos(old_line, old_offs);

    prog_position_free(curs_pos);
    return ret;
}
