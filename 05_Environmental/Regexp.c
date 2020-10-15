#ifndef PCRE2_CODE_UNIT_WIDTH
#define PCRE2_CODE_UNIT_WIDTH 8
#endif

#include <string.h>
#include <pcre2.h>
#include <locale.h>
#include <ncurses.h>

#include "config.h"

#define H_OFFSET    1
#define W_OFFSET    2

#define W_REGEXP_H  3
#define W_STR_H     3
#define W_MSG_H(h)  ((h) - W_REGEXP_H - W_STR_H)

int main(void) {
    // Initital
	setlocale(LC_ALL, "");
    initscr();
    cbreak();
    start_color();
    init_pair(1, COLOR_RED, 0);

    // Get term sizes
    int w, h;
    getmaxyx(stdscr, h, w);
    // Initialize 3 windows
    WINDOW* w_regexp    = newwin(W_REGEXP_H, w, 0, 0);
    WINDOW* w_str       = newwin(W_STR_H, w, W_REGEXP_H, 0);
    WINDOW* w_msg       = newwin(W_MSG_H(h), w, W_REGEXP_H + W_STR_H, 0);
    wborder(w_regexp, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(w_str, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(w_msg, 0, 0, 0, 0, 0, 0, 0, 0);
    keypad(w_regexp, TRUE);
    keypad(w_str, TRUE);

    // Print them
    wrefresh(w_regexp);
    wrefresh(w_str);
    wrefresh(w_msg);
    
    // REGEXP PROJECT Variables
    char s_regexp[w];               // regexp-string
    char s_str[w];                  // search-string
    
    int errnum;
    int i, rc;
    pcre2_code *re;                 // regexp
    PCRE2_SPTR pattern;             // regexp-pcre-str
    PCRE2_SPTR subject;             // search-pcre-str
    PCRE2_SIZE erroffs;
    PCRE2_SIZE *ovector;
    PCRE2_SIZE subject_length;      // search-pcre-str size
    pcre2_match_data *match_data;
    
    while (true) {
        // Get regexp and search-string
        mvwgetstr(w_regexp, H_OFFSET, W_OFFSET, s_regexp);
        mvwgetstr(w_str, H_OFFSET, W_OFFSET, s_str);
        // Proccess regexp searching
        pattern = (PCRE2_SPTR) s_regexp;
        subject = (PCRE2_SPTR) s_str;
        subject_length = (PCRE2_SIZE) strlen((char *)subject);
		#ifdef WITHOUT_UTF
		re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, 0, &errnum, &erroffs, NULL);
		#else
		re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_UCP, &errnum, &erroffs, NULL);
		#endif
        if (!re) {
            rc = -1;
            match_data = 0;
        } else {
            match_data = pcre2_match_data_create_from_pattern(re, NULL);
            rc = pcre2_match(re, subject, subject_length, 0, 0, match_data, NULL);
        }
        // Show results
        wclear(w_regexp);
        wclear(w_str);
        wclear(w_msg);
        mvwprintw(w_msg, H_OFFSET, W_OFFSET, "%s\t", s_str);
        wattron(w_msg, COLOR_PAIR(1));
        wprintw(w_msg, "r'%s'\n", s_regexp);
        wattroff(w_msg, COLOR_PAIR(1));
        if (rc < 0) {
            switch (rc) {
            case PCRE2_ERROR_NOMATCH:
                mvwprintw(w_msg, H_OFFSET + 1, W_OFFSET, "<no match>\n");
                break;
            default:
                mvwprintw(w_msg, H_OFFSET + 1, W_OFFSET, "<matching error>\n");
            }
        } else {
            ovector = pcre2_get_ovector_pointer(match_data);
            
            for (i = 0; i < rc; i++)
                mvwprintw(w_msg, H_OFFSET + 1 + i, W_OFFSET, "%2ld: %.*s\n", ovector[2*i], (int)(ovector[2*i+1] - ovector[2*i]), subject + ovector[2*i]);

            pcre2_match_data_free(match_data);
            pcre2_code_free(re);
        }

        wborder(w_regexp, 0, 0, 0, 0, 0, 0, 0, 0);
        wborder(w_str, 0, 0, 0, 0, 0, 0, 0, 0);
        wborder(w_msg, 0, 0, 0, 0, 0, 0, 0, 0);
        wrefresh(w_regexp);
        wrefresh(w_str);
        wrefresh(w_msg);
    }
    
    endwin();
    return 0;
}
