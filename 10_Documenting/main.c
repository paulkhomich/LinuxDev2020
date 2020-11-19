/**
 * @file main.c
 * Guess the number app
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#include "roman.h"
/** gettext() wrapper */
#define ___(STRING) (gettext(STRING))
/** Path to search locale files */
#define LOCALEPATH "."
/** Maximum in guess row */
#define RANGE	100u
/** Answer buffer size */
#define BUFFER	32
/** Help hint */
#define GUESS_HELP ___("\
Guess-the-number program guess your number in decimal or roman numbers\n\
\n\
Usage: guess [OPTIONS]\n\
\n\
\t--help\t\tprint this help\n\
\t-r\t\tenter in roman-number mode\n\
")

/**
 * Translate decimal @p d to roman
 *
 * @param d Decimal number
 * @returns Roman number
 */ 
char* toRoman(int d) {
	return d2r[d];
}

/**
 * Translate roman @p r to decimal
 *
 * @param r Roman number
 * @returns Decimal number
 */
int toDecimal(char* r) {
	for (size_t i; i <= RANGE; ++i) {
		if (!strcmp(r, d2r[i]))
			return i;
	}

	return -1;
}

int main(int argc, char* argv[argc]) {
	int ROMANMODE = 0;
	setlocale(LC_ALL, "");
	bindtextdomain("guess", LOCALEPATH);
	textdomain("guess");	
	for (size_t i = 0 ; i < argc; ++i) {
		if (!strcmp(argv[i], "-r"))
			ROMANMODE = 1;
		else if (!strcmp(argv[i], "--help"))
			return !printf("%s\n", GUESS_HELP);
	}


	unsigned num = 0;
	char ans[BUFFER];
	if (ROMANMODE) {
		printf(___("Hello! Please, guess the number from I to %s: "), toRoman(RANGE));
		scanf("%s", ans);
		num = toDecimal(ans);
	} else {
		printf(___("Hello! Please, guess the number from 1 to %u: "), RANGE);
		scanf("%d", &num);
	}

	unsigned guess = 0;
	unsigned i = RANGE;
	while (i) {
		if (ROMANMODE)
			printf(___("Is your number greater than %s?: "), toRoman(guess + (i/=2)));
		else
			printf(___("Is your number greater than %d?: "), (guess + (i/=2)));
		scanf("%s", ans);
		if (!strcmp(ans, ___("Yes"))  || 
			!strcmp(ans, ___("+"))    ||
			!strcmp(ans, ___("y"))	  ||	
			!strcmp(ans, ___("True")) || 
			!strcmp(ans, ___("true")))
			guess += (i%2) ? (i + 1) : (i) ? i : 1;
	}
	
	if (ROMANMODE)
		printf(___("I know! You number is %s\n"), toRoman(guess));
	else
		printf(___("I know! You number is %d\n"), guess);

	return EXIT_SUCCESS;
}
