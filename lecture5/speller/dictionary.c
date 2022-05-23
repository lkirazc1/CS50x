// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N] = { NULL };

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int bucket = hash(word);
    for (node *item = table[bucket]; item != NULL; item = item->next)
    {
        if (strcasecmp(item->word, word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    //char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    return (int) tolower(word[0]) % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO:
    // TODO: open dictionary file

    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        return false;
    }

    // TODO read strings from file one at a time

    char current_word[LENGTH + 1];

    while (fgets(current_word, LENGTH + 1, dict) != NULL)
    {
        // strip word of newline
        if (current_word[0] == '\n')
        {
            continue;
        }
        int len = strlen(current_word);
        if (len > 0 && current_word[len - 1] == '\n')
        {
            current_word[len - 1] = 0;
        }
        /*
        for (int i = 0; i < LENGTH + 1; i++)
        {
            if (current_word[i] == '\n')
            {
                current_word[i] = 0;
            }
        }
        */

        // TODO create a new node for each word
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        // TODO hash word to obtain a hash value

        int place = hash(current_word);

        // TODO insert node into hash table at that location

        // loop through start letter values and link word to last node in letter bucket
        for (int i = 0; i < strlen(current_word); i++)
        {
            n->word[i] = current_word[i];
        }
        n->word[strlen(current_word)] = 0;

        n->next = table[place];
        table[place] = n;

    }
    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO

    int words = 0;

    for (int i = 0; i < N; i++)
    {
        for (node *table_value = table[i]; table_value != NULL; table_value = table_value->next)
        {
            words++;
        }
    }

    return words;


}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i];
            table[i] = table[i]->next;
            free(tmp);
        }
    }
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            return false;
        }
    }
    return true;
}

