#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>

#define HEADER          3
#define HEDAERSPACE     4
#define HEDAERSIZE      4
#define MAXLINEW        256
#define NUMLINEW        6
#define KEY_ESCAPE      27


void unfgets(FILE*, char*);
char* strseek(char*, int, int);
int filelines(FILE*);
int showdata(WINDOW*, FILE*, int, int, int, int);

int main(int argc, const char * argv[]) {
    // If filename is not passed
    if (!argv[1]) {
        fprintf(stderr, "usage: %s <filename>\n", argv[0]);
        
        return EXIT_FAILURE;
    }
    // If filename is bad
    FILE* doc = fopen(argv[1], "r");
    if (!doc) {
        fprintf(stderr, "usage: %s <filename>\n", argv[0]);
        
        return EXIT_FAILURE;
    }
    
    // Initializing
	initscr();
	cbreak();
	curs_set(0);
	keypad(stdscr, true);
    noecho();
    
    // Creating windows
    int x, y;
    getmaxyx(stdscr, y, x);
    WINDOW* header; // Header window with filename and filesize
    WINDOW* bodyborder;
    WINDOW* body;   // File lines
    header  = newwin(HEADER, x, 0, 0);
    bodyborder = newwin(y - HEADER, x, HEADER, 0);
    body    = newwin(y - HEADER - 2, x - 2, HEADER + 1, 1); // margin (for placing in border window)
    refresh();
    
    // Rendering header of file and borders
    mvwprintw(header, 1, (x - (int)strlen(argv[0]) - HEDAERSPACE - HEDAERSIZE) / 2, "%s    %d", argv[0], filelines(doc));
    wrefresh(header);
    
    wborder(bodyborder, 0, 0, 0, 0, 0, 0, 0, 0);
    wrefresh(bodyborder);
    
    // Rendering data
    getmaxyx(body, y, x);
    int startline   = 0;        // from which line start
    int startcolumn = 0;        // from which char (in line) start
    
    showdata(body, doc, startline, startcolumn, y, x);
    int ch;
    while ((ch = getch()) && ch != KEY_ESCAPE) {
        switch (ch) {
            case KEY_NPAGE:
                startline += y;
                break;
            case KEY_PPAGE:
                startline = (startline < y ? 0 : startline - y);
                break;
            case KEY_DOWN:
            case ' ':
                ++startline;
                break;
            case KEY_UP:
                if (startline) --startline;
                break;
            case KEY_RIGHT:
                ++startcolumn;
                break;
            case KEY_LEFT:
                if (startcolumn) --startcolumn;
                break;
            default:
                break;
        }
        // Show data && Correct startline (if add too more lines for search)
        startline -= showdata(body, doc, startline, startcolumn, y, x);
    }
    
    endwin();
    return EXIT_SUCCESS;
}

// Show document lines
// Read one more line for lookahead EOF search
// Later this additional line "return" to stream with unfgets
int showdata(WINDOW* win, FILE* doc, int startline, int startcolumn, int num, int width) {
    int numofline = startline;  // start number for numbering
    ++startline;    // for lookahead EOF search
    char line[MAXLINEW];
    // Skip <startline> lines
    while (startline-- && fgets(line, sizeof line, doc)) {};
    numofline -= startline; // correct numbering if reach EOF
    // Clear screen and return line to read-stream
    wclear(win);

    unfgets(doc, line);
    // Print <num> lines or zero (if EOF)
    // With move and limit the line
    while (num-- && fgets(line, sizeof line, doc))
        wprintw(win, "%4.d  %s", numofline++, strseek(line, startcolumn, (width - NUMLINEW)));
    // Reset position in file/screen to init
    wmove(win, 0, 0);
    fseek(doc, 0, SEEK_SET);
    // Return number of NOTREACHED lines (for correct startline in main)
    // (+1) for clampsy last line
    wrefresh(win);
    return (startline + 1);
}

// Return string (seek-like) to doc
void unfgets(FILE* doc, char* str) {
    while (*str++)
        fseek(doc, -1, SEEK_CUR);
}

// Seek in string (if can't seek -> return last sym)
// And limit the string (if need put \0 before real \0)
char* strseek(char* str, int move, int width) {
    unsigned long size = strlen(str);
    str = (size <= move) ? str + size - 1 : str + move; // move START POSITION of the string
    size = strlen(str);
    if (size > width) {  // limit the END POSITION of the string
        str[width - 1] = '\n';  // put NEWLINE for pretty
        str[width] = '\0';      // put EOL
    }
    
    return str;
}

int filelines(FILE* doc) {
    int lines = 0;
    char str[MAXLINEW];
    while (fgets(str, sizeof str, doc))
        ++lines;
    
    fseek(doc, 0, SEEK_SET);
    
    return lines;
}
