// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

/* dictionary size tracker variable */
long size_trck = 0;


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 149021; /* length of dictionary / 3 (rounded to nearest thounsand)  */

// Hash table
node *table[N];

/* declare dictionary file pointer */
FILE *dict_ptr;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    dict_ptr = fopen(dictionary, "r");
    if (dict_ptr == NULL)
    {
        printf("Could not open selected dictionary");
        return false;
    }

    node *w;
    w = malloc(sizeof(node));
    while (fscanf(dict_ptr, "%s", w->word) != EOF)
    {
        size_trck++;
        unsigned int index = hash(w->word);
        w->next = table[index];
        table[index] = w;
        w = malloc(sizeof(node));
    }
    free(w);
    fclose(dict_ptr);
    return true;
}



// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash_value = 5381;
    unsigned int x;

    while((x = tolower(*word++)))
    {
        hash_value = hash_value * 33 + x;
    }
    return hash_value % N;
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    node *tmp = table[index];

    while(tmp != NULL && strcasecmp(tmp->word, word) != 0)
    {
        tmp = tmp->next;
    }
    if(tmp != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return size_trck;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *tmp = table[i];
        node *tmpnxt = NULL;
        if (tmp != NULL)
        {
            tmpnxt = tmp->next;
        }
        else
        {
            continue;
        }

        while(tmpnxt != NULL)
        {
            free(tmp);
            tmp = tmpnxt;
            tmpnxt = tmpnxt->next;
        }
        free(tmp);
    }
    return true;
}