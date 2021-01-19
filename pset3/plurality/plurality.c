#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    //printf("%i\n", candidate_count);
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    //Count vote for each candidate input
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes ++;
            //printf("%i\n", candidates[i].votes);
            return true;
            
        }
    }
    //If candidate input does not match any candidate name in argv
    //return false and program will print incorrect. Vote will not count
    return false; 
    
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //Loop to see who has the most vote, and print out the name
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[0].votes < candidates[i].votes)
        {
            candidates[0].votes = candidates[i].votes;
            candidates[0].name = candidates[i].name;
        }
    }
    printf("%s\n", candidates[0].name);
    
    //Loop again in the list to see if anyone has a tie
    //If so, the program will print multiple winners
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[0].votes == candidates[i].votes && candidates[0].name != candidates[i].name)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}

