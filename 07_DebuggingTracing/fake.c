#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

typedef int (*ul)(const char*);
typedef int (*ulat)(int, const char*, int);

int unlink(const char* path) {
	char pattern[4] = "FIX";
	if (!strstr(path, pattern)) {
		// good, without FIX
		ul original_rm = dlsym(RTLD_NEXT, "unlink");
		original_rm(path);

		return EXIT_SUCCESS;
	}
	// FIX found
	errno = EPERM;

	return EXIT_FAILURE;
}

int unlinkat(int fd, const char* path, int flag) {
	char pattern[4] = "FIX";
	if (!strstr(path, pattern)) {
		// good, without FIX
		ulat original_rm = dlsym(RTLD_NEXT, "unlinkat");
		original_rm(fd, path, flag);

		return EXIT_SUCCESS;
	}
	// FIX found
	errno = EPERM;

	return EXIT_FAILURE;
}

