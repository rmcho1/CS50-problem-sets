#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//This program determines the readability level of the input the user
//enters. The program will count how many letters, words, and sentences
//the user inputs. This information is then calculated into the Coleman
//Liau index. The output is then rounded to the nearest whole number
//and prints out the grade level. 

int main(void)
{
    //Prompts user to input text
    string text = get_string("Text: ");

    float letter_count = 0;
    float word_count = 1;
    float sentence_count = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //Determines the amount of letters
        if (text[i] >= 'A' && text[i] <= 'z')
        {
            letter_count++;
        }

        //Determines the amount of words
        if (text[i] == 32)
        {
            word_count++;
        }
        //test print
        //printf("Letter count: %i\n", letter_count);
        
        //Determines the amount of sentences 
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentence_count ++;
        }
    }
    //tests
    //printf("Letter count: %f\n", letter_count);
    //printf("Word count: %f\n", word_count);
    //printf("Sentence count: %f\n", sentence_count);

    //Information is plugged into the Coleman-Liau index
    float L = (letter_count * 100) / word_count;
    float S = (sentence_count * 100) / word_count;
    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    //tests
    printf("Average letters per 100 words: %f\n", L );
    printf("Average sentences per 100 words: %f\n", S );
    
    int grade = round(index);

    //Ouput prints out the reading grade level
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }


}
