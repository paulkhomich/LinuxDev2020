#include <stdlib.h>

int main(void) {
	int* mem = malloc(10 * sizeof(int));
	for (int i = 0; i < 10; ++i)
		mem[i] = i;

	free(mem);
	free(mem);

	return EXIT_SUCCESS;
}
