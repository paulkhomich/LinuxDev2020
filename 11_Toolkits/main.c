#include <stdio.h>
#include <string.h>
#include <glib.h>

#define SIZE	80
#define DELI	" "

gboolean finder(gpointer key, gpointer value, gpointer user_data) {
	return !strcmp(key, user_data);
}

void iterator(gpointer key, gpointer value, gpointer user_data) {
	printf(user_data, key, *(gint*)value);
}

int main(int argc, char* argv[argc]) {
	// Open file or stdin
	FILE* input = {0};
	if (argc > 1) {
		input = fopen(argv[1], "r");
		if (!input) {
			printf("Error: Usage %s [filename]\n", argv[0]);
			
			return 1;
		}
	} else {
		input = stdin;
	}

	// Create HASH[str->int]
	GHashTable* map = g_hash_table_new(g_str_hash, g_str_equal);

	// Read line from input
	gchar buffer[SIZE+1];

	while (fgets(buffer, SIZE+1, input)) {
		// Split words to [list]
		buffer[strlen(buffer) - 1] = '\0';
		gchar** words = g_strsplit(buffer, DELI, SIZE);
	
		// Find ? inc : strdup + insert
		for (int i = 0; words[i]; i++) {
			gpointer item_ptr = g_hash_table_find(map, (GHRFunc)finder, words[i]);
			if (!item_ptr) {
				gint* tmp = g_new(gint, 1);
				*tmp = 1;
				g_hash_table_insert(map, g_strdup(words[i]), tmp);
			} else {
				(*(gint*)item_ptr)++;
			}
		}
		
		g_strfreev(words);
	}

	g_hash_table_foreach(map, (GHFunc)iterator, "> %s = %d\n");
	g_hash_table_destroy(map);

	return 0;
}
