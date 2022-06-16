#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);
    }
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();

    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Global loop for name checking in candidates arrey
    for (int i = 0; i < candidate_count; i++)
    {
        if ((strcmp(name, candidates[i])) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }

            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count += 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Function declaration
    void swap(pair tab[], int a, int b);

    // Initialization for values
    int max_dif = 0, sorted = 0, index = 0;
    pair temp_pair;

    // Loop to repeat passing from begin to end
    do
    {
        // Loop for one line
        for (int i = sorted; i < pair_count; i++)
        {
            if (max_dif < (preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]))
            {
                max_dif = (preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]);
                temp_pair = pairs[i];
                index = i;
            }
        }
        swap(pairs, sorted, index);
        sorted += 1;
        max_dif = 0;
    }
    while (sorted < pair_count);
}

// Swap in arr tab[], places a with b
void swap(pair tab[], int a, int b)
{
    pair temp_pair;

    temp_pair = pairs[a];
    pairs[a] = pairs[b];
    pairs[b] = temp_pair;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    bool szukaj(int tego, int zakim);

    // Loop for each pair in arr pairs[]
    for (int i = 0; i < pair_count; i++)
    {
        // Seaech for all pairs
        if (!szukaj(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Funkcja szukaj tego = cel, zakim = za jaka komrka
bool szukaj(int tego, int zakim)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Condition zero when circle will close
        if ((locked[i][zakim] == true) && (tego == i))
        {
            return true;
        }

        // Recoursion
        else if ( locked[i][zakim] == true)
        {
            if (szukaj(tego, i) == true)
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // Numers of winners
    int win = 0;
    string w;


    // Loop for ich winner
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; (locked[j][i] == false) && (j < candidate_count); j++)
        {
            if (j == (candidate_count - 1))
            {
                printf("%s\n" ,candidates[i]);
            }
        }
    }
    return;
}

