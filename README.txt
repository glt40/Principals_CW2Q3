Hashtable / Q3 README

== Table of Contents ==
Introduction
Installation
Operation 
Code Layout

INTRODUCTION
============

Welcome to the Hashtable implementation. It resides in hashtable.c. Hashtables are a highly efficient way to
stroe and search for data, in this case strings.

INSTALLATION
============

To run the program, navigate to the containing folder and run the following:
  > gcc CW2Q3.c hashtable.c -o CW2Q3
  > ./CW2Q3
  
OPERATION
============

It is recommended to keep a hastable less than 75-80% full. Adding, removing and searching are all case sensitive.
The following functions are available for use:

  > ht_create()           - Create a new hashtable, size 8192
  > ht_add("string")      - Add the specified string to the table
  > ht_remove("string")   - Remove the specified string from the table
  > ht_search("string")   - Search for the specifies string in the table
  > ht_destroy()          - Destroy the existing table

CODE LAYOUT
============

The CW2Q3.c file contains the main method, which serves to test the functionality of the hashtable by using it's
different functions. It also contains a method to add a large number of names from a file, separated by spaces
