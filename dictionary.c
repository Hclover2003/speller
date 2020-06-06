// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

/* dictionary size tracker variable */
int size_trck = 0;

/* global dictionary load boolean */
bool dic_load = false;


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 48000; /* length of dictionary / 3 (rounded to nearest thounsand)  */

// Hash table
node *table[N];
    
/* declare dictionary file pointer */
FILE *dict_ptr;

bool insert (node *w); /* declaration for supp function to insert word into hash table */
unsigned int size(void); /* declaration for size counter when loading dictionary */

// Loads dictionary into memory, returning true if successful else false
/* moving one given as how this is Step (1) */
bool load(const char *dictionary)
{
    dict_ptr = fopen(dictionary, "r");
    if (dict_ptr == NULL)
    {
        printf("Could not open selected dictionary");
        unload();
        return dic_load = false;
    }


    /* allocate memory for each new word (will use the same block) */ 
    /* TO CONFIRM: Can i get away with not using the word block and scanning directly into the node */
    char *word = malloc(LENGTH * sizeof(char)); /* TO CONFIRM: can i get away with the one malloc and the loop replacing the word each time?  */
    
     /* pointer to dictionary size tracker 
    int *size_trck = malloc(sizeof(int)); */

    node *w;
    /* scan dictionary into hash table one word at a time */
    while (fscanf(dict_ptr, "%s", word) != EOF)
    {
        dic_load = true;
        size();
        
        /* allocate a new block of memory for each new node (will add a new node block for each word)  */
        w = malloc(sizeof(node));

        strcpy(w->word, word); 
        insert(w);
        free(w);
    }
    free(word);
    dic_load = false;
    return true;
}

    bool insert (node *w)
    {
        if (w == NULL) return false;

        int index = hash(w->word); 
        w->next = table[index];
        table[index] = w; 
        return true;
    }


// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash_value = 5381;
    unsigned int x = tolower(*word);

    while(*word != 0)
    {
        hash_value = hash_value * 33 + x;
        x = tolower(*word++);
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
/* increments size tracker by one if the dictionary word pointer (*w) is not null and therefore still iterating 
otherwise returns the tracker val upon call */
unsigned int size(void)
{
    if(dic_load == true)
    {
        size_trck++;
        return size_trck;
    }
    else
    {
        return size_trck;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *tmp = table[i];
        node *tmpnxt = table[i + 1];
        
        if (tmp == NULL && tmpnxt == NULL)
        {
            return false;
        }
        
        else
        {
            while(tmp != NULL && tmpnxt != NULL)
            {
                free(tmp);
                tmp = tmpnxt;
                tmpnxt = tmpnxt->next;
            }
            
            if (tmp != NULL && tmpnxt == NULL)
            {
                free(tmp);
            }
            else
            {
                printf("Something went wrong when freeing the memory -- end of list");
                return false;
            }
        }
    }
    if (!*table)
    {
        printf("Successfully freed each node");
    }
    else
    {
        printf("Error freeing hash tables nodes");
        return false;
    }
    free(table);
    fclose(dict_ptr);
    return true;
}