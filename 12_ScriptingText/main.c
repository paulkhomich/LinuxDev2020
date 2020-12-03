/* COMMENT:: Buffer, 0.0: Thu Dec  3 16:05:46 MSK 2020 */
#include <stdio.h>
#include "buf.h"

int main(void) {
	printf("Growable Buffer Demonstration\n");
	
	float *values = 0;
	for (size_t i = 0; i < 25; i++)
		buf_push(values, rand() / (float)RAND_MAX);
	for (size_t i = 0; i < buf_size(values); i++)
		printf("values[%zu] = %f\n", i, values[i]);
	buf_free(values);	

	return 0;
}
