#include <stdio.h>
#import "hashtable.h"

int main() {
    // Create a new hashtable
    ht_create();
    // Add some strings
    ht_add("Gemma");
    // Add LOADS of strings FIXME ===========================================================

    // Search for strings
    ht_search("Fiona");
    ht_search("Alfie");
    ht_search("Will");
    // Remove strings
    ht_remove("Will");
    ht_remove("Will");
    ht_remove("Lolly");
    // Search for strings after a removal
    ht_search("Will");
    ht_search("Gemma");
    // Creating a new hashtable if one already exists won't work
    ht_create();
    // Remove the table and release memory
    ht_destroy();
    // Removing a hashtable that doesn't exist won't work
    ht_destroy();
    // Operating if there is no existing hashtable won't work
    ht_add("Gemma");
    ht_search("Gemma");
    ht_remove("Gemma");
    return 0;
}
