// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <cs50.h>
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

//word count
int count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int j = hash(word);
    node*tmp = table[j];
    
    while (tmp != NULL)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
        
        tmp = tmp->next;
    }
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int value = 0;
    int len = strlen(word);
    
    for (int i = 0; i < len; i++)
    {
        value += tolower(word[i]);
    }
    
    //make sure hash value is  0 =< value < N
    //note source of information from: https://youtu.be/wg8hZxMRwcw
    value = value % N;
    
    return value;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //open file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    
    //set up hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    
    //read strings from file
    char word[LENGTH + 1];
    while (fscanf(file, "%s\n", word)!= EOF)
    {
        node *new_word = malloc(sizeof(node));
        strcpy(new_word->word, word);
        
        //find what index of the array the word should go into
        int k = hash(word);
        
        //if hash table is empty at index, insert new word
        if (table[k] == NULL)
        {
            new_word->next = NULL;
            table[k] = new_word;
        }
        
        //if hash table is not empty, append new word to front of list
        else
        {
            new_word->next = table[k];
            table[k] = new_word;
        }
        count++;
    }
    
    //close file
    fclose(file);
    
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    //printf("%i\n", count);
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
    
    while (n != NULL)
    {
        node *tmp = n;
        n = n->next;
        free(tmp);
    }

    }
    
    return true;
}
