// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 48000; /* length of dictionary / 3  */

// Hash table
node *table[N];

bool insert (node *w); /* declaration for supp function to insert word into hash table */

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
    if(fscanf(dict_ptr, "%s", dict_live) == NULL) 
    {
        printf("Couldn't copy dictionary into a dynamic array...");
        return false;
    }
    else
    {
        return true;
    }
    
    int index = 0;
    while (dict_live != NULL){
        node *w = malloc(sizeof(node));
        strcpy(w->word, dict_live[index]); /* NEED TO FIX HOW DICTIONARY RUNS THRU; 
        NEEDS TO BE READ AND HASHED WORD BY WORD (MIN 6:23 OF VIDEO) */
        insert(&w);
        index++;
    }
    return true;


    bool insert (node *w)
    {
        if (w == NULL) return false;

        int index = hash(w->word) /* TBU after implementing hash() */
        w->next = table[index];
        table[index] = w; 
        return true;
    }

    
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    int wlen = strlen(word);    
    unsigned long hash_value = 5381;
    unsigned int x = *word;
    x = tolower(x);

    while(*word != NULL)
    {
        hash_value = hash_value * 33 + x;
        x = *word++;
        x = tolower(x);
    }
    return hash_value % N;
    



    /* return 0; not sure how to have hash() return 0 yet */
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
