#include <stdio.h>
#import "hashtable.h"

int main() {
    // Create a new hashtable
    ht_create();
    // Add some strings
    ht_add("Gemma");
    ht_add("Fiona");
    ht_add("Will");
    ht_add("Justin");
    ht_add("Maeva");
    // Search for strings
    ht_search("Fiona");
    ht_search("Alfie");
    // Remove strings
    ht_remove("Will");
    ht_remove("Will");
    ht_remove("Lolly");
    // Search for strings after a removal
    ht_search("Will");
    ht_search("Gemma");
    printf("complete");
    // Remove the table and release memory
//    ht_destroy();
//    // Operate if there is no existing hashtable
//    ht_add("Gemma");
//    ht_search("Gemma");
//    ht_remove("Gemma");
    return 0;
}
