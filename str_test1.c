// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

#define LENGTH 45

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int main(void)
{
node *test = calloc(1, sizeof(node));
strcpy(test->word[0], "c");
strcpy(test->word[1], "a");
strcpy(test->word[2], "t");

printf("%c\n", test->word[1]);
}
/* THIS IS CAUSING THE SEG FAULT IN DICTIONARY.C / SPELLER */