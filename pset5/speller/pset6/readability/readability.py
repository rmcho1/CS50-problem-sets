from cs50 import get_string
from cs50 import get_int
import math

# This program determines the readability level of the input the user
# enters. The program will count how many letters, words, and sentences
# the user inputs. This information is then calculated into the Coleman
# Liau index. The output is then rounded to the nearest whole number
# and prints out the grade level. 
    
def coleman_liau_index(text):
    
    # variables
    letter_count = 0
    word_count = 1
    sentence_count = 0

    # count # of letters, words, and sentences
    for i in range(len(text)):
    
        # determines the amount of letters
        if (text[i] >= 'A' and text[i] <= 'z'):
            letter_count += 1
    
        # determines the amount of words
        if (text[i] == " "):
            word_count += 1
        
        # determines the amount of sentences
        if (text[i] == '!' or text[i] == '.' or text[i] == '?'):
            sentence_count += 1
    
    # tests
    # print("letters:" + str(letter_count))
    # print("words:" + str(word_count))
    # print ("sentences: " + str(sentence_count))
    
    # Plug information into coleman-liau index
    letter_index = (letter_count * 100) / word_count
    sentence_index = (sentence_count * 100) / word_count
    index = (0.0588 * letter_index) - (0.296 * sentence_index) - 15.8
    
    # tests
    # print("Average letters per 100 words:" + str(letter_index))
    # print("Average sentences per 100 words:" + str(sentence_index))
    # print(index)
    
    grade = int(round(index))
    
    # Determine grade level
    if (grade < 1):
        print("Before Grade 1")

    elif (grade > 16):
        print("Grade 16+")
    
    else:
        print("Grade " + str(grade))


# Gets text from user
text = get_string("Text: ")
coleman_liau_index(text)
