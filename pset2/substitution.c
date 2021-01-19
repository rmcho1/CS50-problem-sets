#include <cs50.h>
#include <stdio.h>
#include <string.h>

//This program implements a substitution cipher, where we encrypt
//a message by replacing every letter with another letter.

bool check_length(string s);
bool check_alphabetical(string s);
bool check_repetition(string s);


int main(int argc, string argv[])
{
    //get key on command line
    if (argc != 2)
    {
        printf("Missing Key\n");
        return 1;
    }

    if (argc == 2)
    {
        //validate key
        string s = argv[1];
        check_length(s);
        if (check_length(s) == 0)
        {
            printf("Invalid. Key must contain 26 characters.\n");
            return 1;
        }
        
        check_alphabetical(s);
        if (check_alphabetical(s) == 0)
        {
            printf("Invalid. Key must contain alphabets.\n");
            return 1;
        }
        
        check_repetition(s);
        if (check_repetition(s) == 0)
        {
            printf("Invalid. Key cannot have any repetitions.\n");
            return 1;
            
        }



        if (check_length(s) == 1 && check_alphabetical(s) == 1 && check_repetition(s) == 1)
        {
            //if key is validated, get plaintext from user 
            string x = get_string("Plaintext: ");
            int n = strlen(s);
            int m = strlen(x);
            int key_array [26];
            int count = 65;
            
            //Encryption: Since there are 26 letters, an array of 26 elements 
            //is created. I will need to map each command line letter to
            //the alphabet in alphabetical order. Since A = 65, 
            //I will take the value of each command line letter 
            //and subtract it by 65 to get the difference. 
            //Then, I will assign that as the value of each key_array element.
            
            
            for (int i = 0; i < n; i++)
            {
                //convert command line text to all upper case letters
                if (s[i] > 96 && s[i] < 123)
                {
                    s[i] = s[i] - 32;
                }
                key_array[i] = s[i] - count;
                //printf("%s%c\n","s char: ",s[i]);
                //printf("%s%i\n","count : ",count);
                //printf("%s%i\n\n","KEY ARRAY: ",key_array[i]);
                count++;

            }
            
            //Once the for loop is through, the program will print
            //Ciphertext. After the print out, the program will then 
            //take the plain text to decrypt the message.
            
            printf("%s", "ciphertext: ");
           
            //This for loop will ensure that all plain texts will be converted to 
            //an upper case letter. I added a lowercase counter to keep track of which
            //letters are lower case. 
            for (int i = 0; i < m; i++)
            {
                int lowercase = 0;
                int punctuation = 0;
                if (x[i] > 96 && x[i] < 123)
                {
                    lowercase = 1;
                    x[i] = x[i] - 32;
                }
                //if x[i] is a punctuation or number, it will be left alone
                if (x[i] > 31 && x[i] < 65)
                {
                    punctuation = 1;
                    x[i] = x[i];
                }
                //65 is uppercase A
                //x[i] is the character value of the input letter we are trying to encrypt. 
                //subtracting by 65 means that it makes it 0 offset to our array an A
                //would give us array index 0 (which is the first letter of the 26 character code)
                char decode = key_array[x[i] - 65]; 
                //printf("%s%i"," key_array[x[i]-65]: ",key_array[x[i]-65]); 
                //key_array is the array we are using to store how many chracters to go up or down by in our encription
              
              
                /*printf("%s%c\n","input x[i] ",x[i]);//this is the character we are encrypting
                printf("%s%c\n\n","key_array[65-x[i]] ",x[i]+decode);//this is where we apply our character value offset to the second input 
                to get our encrypted letter*/
        
                //To decrypt, we will now add the decode value to the plain text character.
                //Now that all the texts are in upper case, we will go back to which letters
                //were tracked as lowercase. If it is lowercase, we will convert it back by 
                //adding 32. If not, we will leave alone. If text is a punctuation or number, 
                //it will print out as is.
                if (lowercase == 1)
                {
                    printf("%c", x[i] + decode + 32);
                }
                else if (punctuation == 1)
                {
                    printf("%c", x[i]);
                }
                else
                {
                    printf("%c", x[i] + decode);
                }
            }
            printf("\n");
            //printf("ciphertext: %s\n", x);
        }

    }
    

}

//Function to check string length
bool check_length(string s)
{
    int n = strlen(s);
    if (n == 26)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


//Function to check if string is alphabetical
bool check_alphabetical(string s)
{
    bool check_alphabetical = 1;
    int n = strlen(s);
    for (int i = 0; i < n; i++)
    {
        if (s[i] < 'A' || s[i] > 'z')
        {
            check_alphabetical = 0;
        }
    }

    if (check_alphabetical == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


//Function to check any repetition in string
bool check_repetition(string s)
{
    bool check_repetition = 1;
    int n = strlen(s);
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (s[i] == s[j])
            {
                check_repetition = 0;
            }
        }
    }
    if (check_repetition == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}