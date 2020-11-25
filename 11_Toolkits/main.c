#include <stdio.h>
#include <string.h>
#include <glib.h>

#define SIZE	80
#define DELI	" "

gboolean finder(gpointer key, gpointer value, gpointer user_data) {
	return !g_ascii_strcasecmp(key, user_data);
}

void iterator(gpointer key, gpointer map) {
	gpointer value = g_hash_table_find(map, (GHRFunc)finder, key);
	printf("%d\t%s\n", *(gint*)value, key);
}

gint comparator(gconstpointer a, gconstpointer b, gpointer map) {
	gpointer item_a_ptr = g_hash_table_find(map, (GHRFunc)finder, (gpointer)a);
	gpointer item_b_ptr = g_hash_table_find(map, (GHRFunc)finder, (gpointer)b);

	return *(gint*)item_b_ptr - *(gint*)item_a_ptr;
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

	// Create HASH[str->int] + LIST[str]
	GHashTable* map = g_hash_table_new(g_str_hash, g_str_equal);
	GSList* list = {0};

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
				// Add to HASH
				gint* tmp = g_new(gint, 1);
				*tmp = 1;
				gchar* strtmp = g_strdup(words[i]);
				g_hash_table_insert(map, strtmp, tmp);
				// Add to LIST
				g_hash_table_lookup(map, words[i]);
				list = g_slist_append(list, strtmp);
			} else {
				(*(gint*)item_ptr)++;
			}
		}
		
		g_strfreev(words);
	}

	// Sort LIST (using HASH)
	list = g_slist_sort_with_data(list, (GCompareDataFunc)comparator, map);

	// Print LIST (using HASH)	
	g_slist_foreach(list, iterator, map);
	
	g_hash_table_destroy(map);
	g_slist_free(list);

	return 0;
}
