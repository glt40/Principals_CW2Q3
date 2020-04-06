#include "hashtable.h"

int *hashtable;

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

/* This function initialises a new table by allocating a fixed amount of memory and clearing it
 * The pointer to the table is stored in a global variable
 * The table has space for 1024 strings, but it is recommended to store up to 75% of that, or 768 strings total
 */
void new_hashtable() {

}

/* Function finds the next empty space in the hashtable starting from a given index
 * Returns an index, or returns "1024" as an error if table is full
 */
int find_empty(int start) {
    // collision handling: if the index calculated is full, find the next empty one
    for (int i = 0; i < 1024; i++) {
        if (hashtable[(start + i) % 1024] == 0) {
            // This allows for wraparound in the array
            return (i + start) % 1024;
        }
    }
    // If no empty spaces are found return 1024
    return 1024;
}

/* This function adds a string to the hashtable by hashing the string,
 * then using the modulo division by 1024 to generate an index
 * Collision handling is done via Open addressing/ Linear probing
 */
void ht_add(char *string) {
    int str_len = find_len(string);
    int dest_index = (int)(joaat_hash(string) % 1024);
    // Find the next empty index with find_empty()
    dest_index = find_empty(dest_index);
    if (dest_index == 1024) {
        // if there are no free spaces left, the string can't be added
        printf("Error adding string. Table is full.\n");
        return;
    }
    // adding string (array) to the table (array of arrays) at index i
    // Don't forget the null char
    for (int j = 0; j <= str_len; j++) {
        // FIX FOR UNEXPECTED SECOND INDEX ==========================================================
        hashtable[dest_index][j] = string[j];
    }
    printf( "String successfully added to table.\n");
}

/* Function takes a char pointer to a string and returns the index at which that string is found
 * Returns "1024" as an error if table is full or if string isn't found
 */
int ht_find_ind(char *string) {
    int str_len = find_len(string);
    int dest_index = (int)(joaat_hash(string) % 1024);
    int stop_index = find_empty(dest_index);
    int num_items;
    bool full_match = false;
    int i;
    // The string won't always be in the expected index, in which case you have to trawl up to the next empty index
    // if there are no empty indexes, trawl the whole table
    if (stop_index == 1024) {
        num_items = 1024;
    } else {
        num_items = stop_index - dest_index;
    }
    for (i = 0; i < num_items; i++) {
        // FIX FOR TWO INDICES ==================================================
        if (hashtable[(dest_index + i) % 1024][0] == string[0]) {
            full_match = true;
            for (int j = 1; j < str_len; j++) {
                if (hashtable[(dest_index + i) % 1024][j] != string[j]) {
                    full_match = false;
                }
            }
        }
    }
    return full_match ? (dest_index + i) % 1024 : 1024;
}

/* This function removes a string from the hashtable
 */
void ht_remove(char *string) {
    int str_len = find_len(string);
    int dest_index = ht_find_ind(string);
    if (dest_index == 1024) {
        // error given
        printf("Error, string not found in table.\n")
    } else {
        for (int i = 0; i < str_len; i++) {
            // char T stands for tombstone, and it allows the table to be searched after items have been removed
            hashtable[dest_index][i] = 'T';
        }
        printf("String successfully removed.\n");
    }
}

/* This function
 */
bool ht_search(char *string) {
    int dest_index = ht_find_ind(string);
    if (dest_index == 1024) {
        // String not found
        printf("\"%s\" not found.\n", string);
    } else {
        // FIX FOR TWO INDEXES ===================================================
        printf("\"%s\" found at index %d, memory location %p.\n", string, dest_index, *hashtable[dest_index][0]);
    }
}

/* This function frees allocated memory and clears the existing hashtable
 */
void ht_destroy() {

}