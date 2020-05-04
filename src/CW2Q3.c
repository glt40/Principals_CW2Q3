#include <stdio.h>
#include "hashtable.h"

/* Adds around 5000 strings from a file containing given names
 * The file has names in UPPERCASE separated by spaces
 */
void test_add() {
    FILE *fp;
    char buff[255];
    int items_num = 5163;
    char *filename = "names2.txt";
    // Open the file in read mode
    fp = fopen(filename, "r");
    // Keep reading until loop is broken
    while(true) {
        for (int i = 0; i < items_num; i++) {
            // Read up until next space
            fscanf(fp, "%s", buff);
            ht_add(buff);
        }
        break;
    }
    fclose(fp);
}

// Main method, test behaviour of hashtable.c
int main() {
    // Create a new hashtable
    ht_create();
    // Add some strings from a file
    test_add();
    // Search for strings
    ht_search("FIONA");
    ht_search("CLEOPATRA");
    ht_search("WILL");
    // Remove strings
    ht_remove("WILL");
    ht_remove("WILL");
    ht_remove("LOLLY");
    // Search for strings after a removal
    ht_search("WILL");
    ht_search("GEMMA");
    // Creating a new hashtable if one already exists won't work
    ht_create();
    // Remove the table and release memory
    ht_destroy();
    // Removing a hashtable that doesn't exist won't work
    ht_destroy();
    // Operating if there is no existing hashtable won't work
    ht_add("GEMMA");
    ht_search("GEMMA");
    ht_remove("GEMMA");
    return 0;
}
