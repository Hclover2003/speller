// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1; /* TBU!! */

// Hash table
node *table[N];

// Loads dictionary into memory, returning true if successful else false
/* moving one given as how this is Step (1) */
bool load(const char *dictionary)
{
    FILE *dict_ptr = fopen(dictionary, "r");
    if (dict_ptr == NULL)
    {
        printf("Could not open %s...\n", dict_ptr);
        unload();
        return false;
    }
    
    /* //determine size of dictionary file */
    fseek(dict_ptr, 0, SEEK_END);
    int dict_size = ftell(dict_ptr);
    rewind(dict_ptr);

    /* allocate memory for each node */
    node *dict_live = malloc(dict_size * sizeof(int));
    
    /* scan dictionary into allocated array */
    if(fscanf(dict_ptr, "%s", dict_live) == NULL) //THIS IS WRONG. NEEDS TO BE DONE ONE WORD AT A TIME
    /* fscanf will return EOF once it reaches end -- should be a loop */
    {
        printf("Couldn't copy dictionary into a dynamic array...");
        return 
    }
    
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    node *d = malloc(sizeof(node));

    return 0;
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
