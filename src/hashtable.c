#include "hashtable.h"

// Initialise data structure
typedef struct {
   char **ht_record;
} ht_hashtable;

// Initialise global variables
ht_hashtable hashtable;
int table_size = 1024;

/*The following function finds the length of a string, given a pointer to the first char, returning an int
 */
int find_len(char *string) {
    int i=0;
    while (string[i] != 0) {
        i++;
    }
    return i;
}

/* This hashing algorithm was created by Bob Jenkins in an article in "Dr. Dobbs" in September 1997
 * It is fast and due to its performance, few collisions are expected
 * The algorithm is called Jenkins' one-at-a-time hash and returns a 32-bit unsigned integer
 */
__uint32_t joaat_hash(char *key) {
    size_t key_len = sizeof(find_len(key));
    __uint32_t hash = 0;
    size_t i;

    for (i = 0; i < key_len; i++) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

/* This function initialises a new table by allocating a fixed amount of memory and clearing it to NULL
 * The pointer to the table is stored in a global variable
 * The table has space for 1024 strings, but it is recommended to store up to 75% of that, or 768 strings total
 */
void ht_create() {
    // Allocate the memory
    hashtable.ht_record = (char **)malloc(sizeof(char *) * table_size);
    // Set all records to null
    for (int i = 0; i < table_size; i++) {
        hashtable.ht_record[i] = NULL;
    }
    printf("Table created.\n");
}

/* Function finds the next empty space in the hashtable starting from a given index
 * Returns an index, or returns "1024" as an error if table is full
 */
int find_empty(int start) {
    // collision handling: if the index calculated contains something, find the next empty one
    for (int i = 0; i < table_size; i++) {
        if (hashtable.ht_record[(start + i) % table_size] == NULL) {
            // This allows for wraparound in the array
            return (i + start) % table_size;
        }
    }
    // If no empty spaces are found return 1024
    return table_size;
}

/* This function adds a string to the hashtable by hashing the string,
 * then using the modulo division by 1024 to generate an index
 * Collision handling is done via Open addressing/ Linear probing
 */
void ht_add(char *string) {
    int str_len = find_len(string);
    int dest_index = (int)(joaat_hash(string) % table_size);
    // Find the next empty index with find_empty()
    dest_index = find_empty(dest_index);
    if (dest_index == table_size) {
        // if there are no free spaces left, the string can't be added
        printf("Error adding string. Table is full.\n");
        return;
    }
    // adding string (array) to the table (array of arrays) at index i
    // Don't forget the null char
    hashtable.ht_record[dest_index] = malloc(sizeof(char)*(str_len+1));
    for (int j = 0; j <= str_len; j++) {
        hashtable.ht_record[dest_index][j] = string[j];
    }
    printf( "String successfully added to table.\n");
}

/* Function takes a char pointer to a string and returns the index at which that string is found
 * Returns "1024" as an error if table is full or if string isn't found
 */
int ht_find_ind(char *string) {
    int str_len = find_len(string);
    int dest_index = (int)(joaat_hash(string) % table_size);
    int stop_index = find_empty(dest_index);
    int num_items;
    bool full_match = false;
    int i;
    // The string won't always be in the expected index, in which case you have to trawl up to the next empty index
    // if there are no empty indexes, trawl the whole table
    if (stop_index == table_size) {
        num_items = table_size;
    } else {
        num_items = stop_index - dest_index;
    }
    for (i = 0; i < num_items; i++) {
        if (hashtable.ht_record[(dest_index + i) % table_size][0] == string[0]) {
            full_match = true;
            for (int j = 1; j < str_len; j++) {
                if (hashtable.ht_record[(dest_index + i) % table_size][j] != string[j]) {
                    full_match = false;
                }
            }
        }
    }
    return full_match ? (dest_index + i) % table_size : table_size;
}

/* This function removes a string from the hashtable using the ht_find_ind() function
 * Prints an error message if the string isn't found
 */
void ht_remove(char *string) {
    int str_len = find_len(string);
    int dest_index = ht_find_ind(string);
    if (dest_index == table_size) {
        // error given
        printf("Error, string not found in table.\n");
    } else {
        // de and then re-allocate memory for this function to change it
        free(hashtable.ht_record[dest_index]);
        hashtable.ht_record[dest_index] = malloc(sizeof(char)*(str_len+1));
        for (int i = 0; i < str_len; i++) {
            // char T stands for tombstone, and it allows the table to be searched after items have been removed
            hashtable.ht_record[dest_index][i] = 'T';
        }
        printf("String successfully removed.\n");
    }
}

/* This function is called to search for a given string, printing whether or not it was found,
 * as well as information on its location if it is in the table
 */
bool ht_search(char *string) {
    int dest_index = ht_find_ind(string);
    if (dest_index == table_size) {
        // String not found
        printf("\"%s\" not found.\n", string);
    } else {
        printf("\"%s\" found at index %d, memory location %p.\n", string, dest_index, (void *)&hashtable.ht_record[dest_index]);
    }
}

/* This function frees allocated memory and clears the existing hashtable
 */
void ht_destroy() {
    // Memory needs to be released and the hashtable cleared
    // First set everything to NULL type
    for (int i = 0; i < table_size; ++i) {
        int j = 0;
        do {
            hashtable.ht_record[i][j] = (char)NULL;
            j++;
        } while (hashtable.ht_record[i][j] != (char)NULL);
    }
    // Release the individual records
    for (int i = 0; i < table_size; i++) {
        free(hashtable.ht_record[i]);
    }
    // Release the table
    free(&hashtable);
    printf("Hashtable destroyed.");
}