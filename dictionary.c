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
const unsigned int N = 38000; /* length of dictionary / 3 (rounded to nearest thounsand)  */

// Hash table
node *table[N];
    

// Loads dictionary into memory, returning true if successful else false
/* moving one given as how this is Step (1) */
bool load(const char *dictionary)
{
    /* declare dictionary file pointer */
    FILE *dict_ptr = fopen(dictionary, "rb");
    if (dict_ptr == NULL)
    {
        printf("Could not open selected dictionary");
        return false;
    }
    
    /* figure out file size */
    fseek(dict_ptr, 0, SEEK_END);
    long filesize = ftell(dict_ptr);
    rewind(dict_ptr);
    long totalsize = filesize * LENGTH; 

    /* array to store the dictionary locally, thereby making it faster to iterate thru when setting up the hash table  */
    char *dictionary_live = calloc(totalsize, sizeof(char));
    
    fread(dictionary_live, sizeof(char), totalsize, dict_ptr);

    char word[LENGTH] = {}; 
    node *w;

    /* now we can iterate thru the dictionary without having to use fscanf or fgets each time, which slows down the runtime  */
    w = calloc(1, sizeof(node));
    int dc = 0; 
    int lc = 0;
    printf("%c\n", dictionary_live[dc]);
    while (dictionary_live[dc] != 0)
    {
        if (dictionary_live[dc] == '\n')
        {
            size_trck++;
            int index = hash(w->word); 
            w->next = table[index];
            table[index] = w; 
            w = calloc(1, sizeof(node));
            dc++;
            lc = 0;
            continue;
        }
        else
        {
            w->word[lc] = dictionary[dc];
            lc++;
            dc++;
        }   
    }
    free(dictionary_live);
    fclose(dict_ptr);
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash_value = 5381;
    unsigned int x = *word;

    while(*word != 0)
    {
        hash_value = hash_value * 33 + x;
        x = *word++;
    }
    return hash_value % N;

    /* return 0; not sure how to have hash() return 0 yet */
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);
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
        return false; /* clean this up once finished; figure out the shortest form acceptable */
    }
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
/* increments size tracker by one if the dictionary word pointer (*w) is not null and therefore still iterating 
otherwise returns the tracker val upon call */
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
     }
    return true;
}