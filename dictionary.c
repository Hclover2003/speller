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


    /* allocate (1) memory for each new word (will use the same block) and 
    (2) memory for each new node (will add a new node block for each word)  */
    /* TO CONFIRM: Can i get away with not using the word block and scanning directly into the node */
    char *word = malloc(LENGTH * sizeof(char)); /* TO CONFIRM: can i get away with the one malloc and the loop replacing the word each time?  */
    node *w = malloc(sizeof(node));
    
    /* scan dictionary into hash table one word at a time */
    while (fscanf(dict_ptr, "%s", word) != EOF)
    {
        int index = 0;
        strcpy(w->word, word); 
        insert(&w);
        index++;
        node *w = malloc(sizeof(node)); /* TO CONFIRM: Is this right? Using same function iterably with the intent of creating a new block each time */
        return true;
    }
    free(word);
    free(w);


    bool insert (node *w)
    {
        if (w == NULL) return false;

        int index = hash(w->word) /* TBU after implementing hash() */
        w->next = table[index];
        table[index] = w; 
        return true;
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
    int index = hash(word);
    node *tmp = table[index];
    
    while(tmp != NULL && strncmp(tmp->word, word, LENGTH) != 0)
    {
        tmp = tmp->next;
    }
    if(tmp != NULL)
    {
        return true;
    }
    else
    {
        return false; /* clean this up once finished; figure out the shortest form acceptable */
    }
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
