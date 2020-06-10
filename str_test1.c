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

char line[50][50] = {{0}};
line[0][0] = 'c';
line[0][1] = 'a';
line[0][2] = 't';
line[0][3] = '\n';

strcpy(test->word, line[0]);

int i = 0;
while(test->word[i] != 0)
{
    printf("%c", test->word[i]);
    i++;
}
printf("\n");

char text[LENGTH] = "CaT";
unsigned int texts = tolower(text[0]);
int answer = strcasecmp(test->word, text);
printf("%i\n", answer); 


}