// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.h>

#include "dictionary.h"

// header for hash function
#include <stdint.h> /* Replace with <stdint.h> if appropriate */
#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) || defined(_MSC_VER) || defined(__BORLANDC__) || defined(__TURBOC__)
#define get16bits(d) (*((const uint16_t *)(d)))
#endif

#if !defined(get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8) + (uint32_t)(((const uint8_t *)(d))[0]))
#endif

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    node *head = table[hash(word)]->next;

    while (true)
    {
        if ((head->next == NULL) && (!strcasecmp(head->word, word)))
        {
            printf("To jest check gdzie jest koniec function\n");

            return false;
        }

        else if (strcasecmp(head->word, word))

        {
            printf("To jest check gdzie jest check positive function\n");

            return true;
        }
        head = head->next;
    }
}

// Hashes word to a number

unsigned int hash(const char *word)
{
    int len = N;
    printf("To jest poczatek HASH:\nlen = %i\nN = %i\n", len, N);
    uint32_t hash = len, tmp;
    int rem;

    if (len <= 0 || word == NULL)
        return 0;

    rem = len & 3;
    len >>= 2;

    /* Main loop */
    for (; len > 0; len--)
    {
        hash += get16bits(word);
        tmp = (get16bits(word + 2) << 11) ^ hash;
        hash = (hash << 16) ^ tmp;
        word += 2 * sizeof(uint16_t);
        hash += hash >> 11;
    }

    /* Handle end cases */
    switch (rem)
    {
    case 3:
        hash += get16bits(word);
        hash ^= hash << 16;
        hash ^= ((signed char)word[sizeof(uint16_t)]) << 18;
        hash += hash >> 11;
        break;
    case 2:
        hash += get16bits(word);
        hash ^= hash << 11;
        hash += hash >> 17;
        break;
    case 1:
        hash += (signed char)*word;
        hash ^= hash << 10;
        hash += hash >> 1;
    }

    /* Force "avalanching" of final 127 bits */
    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    printf("To jest koniec HASH:\nlen = %i\nN = %i\nhash = %i\n\n", len, N, hash);

    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Create dictionary pointer and open file
    FILE *dict = fopen(dictionary, "r");

    // Create temporaty node pointer to read file
    node *head = malloc(sizeof(node));
    if (head == NULL)
    {
        printf("To jest sprawdzenie czy head wskazuje na NULL\n");
        return false;
    }

    char a = 0;
    int index = 0;

    while (fread(&a, sizeof(char), 1, dict))
    {
        if (a == '\0')
        {
            index = 0;

            // Read dictonary

            printf("Word: %s\n\n", head->word);
            // temp node first in hash table means stands as head of
            if (table[hash(head->word)]->next == NULL)
            {
                printf("To jest load gdzie jest zamienilo table head\n");
                table[hash(head->word)]->next = head;
            }

            // Not head
            else
            {
                node *temp = malloc(sizeof(node));
                if (temp == NULL)
                {
                    return false;
                }

                temp = head;
                temp->next = table[hash(temp->word)]->next;

                // tu moze byc &temp
                table[hash(temp->word)]->next = temp;
            }
        }

        else
        {
            head->word[index] = a;
            index++;
        }
    }

    fclose(dict);
    free(head);
    printf("To jest load gdzie jest koniec funkcjis open function\n");

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int counter = 0;
    node *head = table[0]->next;

    for (int i = 0; i <= N; i++)
    {
        while (head->next != NULL)
        {
            counter++;
            head = head->next;
        }
        head = table[i];
    }
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    return false;
}
