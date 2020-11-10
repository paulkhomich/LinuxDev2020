#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#define ___(STRING) (gettext(STRING))
#define LOCALEPATH "."

#define RANGE	100u
#define BUFFER	32

int main(void) {
	setlocale(LC_ALL, "");
	bindtextdomain("guess", LOCALEPATH);
	textdomain("guess");	

	unsigned num = 0;
	printf(___("Hello! Please, guess the number from 1 to %u: "), RANGE);
	scanf("%d", &num);

	char ans[BUFFER];
	unsigned guess = 0;
	unsigned i = RANGE;
	while (i) {
		printf(___("Is your number grater than %d?: "), (guess + (i/=2)));
		scanf("%s", ans);
		if (!strcmp(ans, ___("Yes"))  || 
			!strcmp(ans, ___("yes"))  || 
			!strcmp(ans, ___("+"))    ||
			!strcmp(ans, ___("y"))	  ||	
			!strcmp(ans, ___("True")) || 
			!strcmp(ans, ___("true")))
			guess += (i%2) ? (i + 1) : (i) ? i : 1;
	}

	printf(___("I know! You number is %d\n"), guess);

	return EXIT_SUCCESS;
}
