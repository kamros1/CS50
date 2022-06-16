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
const unsigned int N = 1000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    printf("CHECK FUNCTION poczatek\n");
    // TODO
    int hashnumber = hash(word);

    node *head = table[hashnumber];

    do
    {
        if (strcasecmp(head->word, word))
        {
//            printf("Slowo jest w slowniku\n");
           printf("CHECK FUNCTION koniec przed return true\n\n");
            return true;
        }

        else
        {
            head = head->next;
//            printf("zamiana head na head->next\n");
        }

    } while (head->next != NULL);
    printf("CHECK FUNCTION koniec przed return false\n\n");
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //    printf("HASH na poczatku funkcji:\nword:%c\n\n", *word);
    int len = N;
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

    if (hash < 0)
    {
        hash *= hash * (-1);
    }
    hash %= N;

//    printf("HASH przed return funkcji:\nhash = %i\n", hash);
    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    printf("TO JEST POCZATEK FUNCJI LOAD\n");
    // TODO
    // Create dictionary pointer and open file
    FILE *dict = fopen(dictionary, "r");

    // Create temporaty node pointer to read file
    node *head = malloc(sizeof(node));
    head->next = NULL;
    if (head == NULL)
    {
        free(head);
        return false;
    }

    /* Initialization for variation
a is one char reprezentative to create whole word
index number to create string
hashnumber is result of hash function for certian word*/
    char a;
    int index = 0;
    int hashnumber = 0;

    // Loop to read whole file until EOF
    while (fread(&a, sizeof(char), 1, dict))
    {

        // Recognize end of word as next line in file
        if (a == '\n')
        {
//            printf("TO JEST POCZATEK NOWEGO SLOWA\n");

            // Mark end of word
            head->word[index] = '\0';
            index = 0;

            // Update hashnumber
            hashnumber = hash(head->word);
//          printf("NIE W FUNKCI head->Word:%s\nhash function wynik:%i\n", head->word, hash(head->word));

            // Insert word if there is space
            if (table[hashnumber] == NULL)
            {
//                printf("Przed podstawieniem w tabele table[hashnumber]:\nword:%s\n", table[hashnumber]->word);
                table[hashnumber] = head;
//                printf("Po wstawieniu HEAD do table[hashnumber]:\nWORD:%s\n\n\n", table[hashnumber]->word);
            }

            // Find and create new place
            else
            {
//                printf("    Miejsce w tabeli jest zajete.\nPoczatek wstawiania node do listy\n");

                // Create spot in memory for new node
                node *temp = malloc(sizeof(node));
                if (temp == NULL)
                {
                    return false;
                }
                temp = head;

                // Replace correct spot to list in hash tabel
                temp->next = table[hashnumber]->next;
                table[hashnumber]->next = temp;
//                printf("Wstawilo head do hash table\n");
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
    printf("LOAD FUNCTION KONIEC\n\n");

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    printf("\n\nSIZE FUNCTION\n poczatek\n");
    int counter = 0;
    node *head = table[0];

    for (int i = 0; i < N; i++)
    {
        if (head->next == NULL)
        {
            continue;
        }
        while (head != NULL)
        {
            counter++;
            head = head->next;
        }
        head = table[i]->next;
    }
    printf("\n\nSIZE FUNCTION\n koniec counter:%i\n", counter );
    return counter;
}

void erase(node *pointer)
{
    if (pointer->next == NULL)
    {
        free(pointer->next);
    }
    else
    {
        erase(pointer->next);
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    printf("UNLOAD FUNCTION poczatek\n");

    int n = N;
    node *head = table[n];

    // Pass through all avialable cells in table
    for (; n >= 0; n--)
    {
        *head = *table[n];
        erase(head);

    }
    printf("UNLOAD FUNCTION koniec\n\n") ;
    return true;
}

