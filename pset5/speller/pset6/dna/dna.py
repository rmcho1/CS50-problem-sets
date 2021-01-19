from csv import reader, DictReader
from sys import argv

#Check the length of arguments. If not correct, exit program
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit()
    
#Transfer STR data from CSV into a list
with open(argv[1]) as csv_file:
    database = reader(csv_file)
    #for each row in the CSV file, remove the name which is 0, and keep only STR info
    for row in database:
        str_info = row
        str_info.pop(0)
        break

#Open sequence text file:
with open(argv[2]) as txt_file:
    dna_info = reader(txt_file)
    #To iterate the row
    for row in dna_info:
        dna_list = row

#List and dictionary to store dna sequences
dna = dna_list[0]
sequence = {}


#copy the list into the dictionary
# 0 is name, and 1 is the STR
for str in str_info:
    sequence[str] = 1

#go through all DNA sequence and count # of STRs
for key in sequence:
    length = len(key)
    max_length = 0 
    #for temporary max length
    tmp_max_length = 0
    for i in range(len(dna)):
        while tmp_max_length > 0:
            tmp_max_length -= 1
            continue

        #if sequence is equal to the key, then start counting again
        if dna[i: i + length] == key:
            while dna[i - length: i] == dna[i: i + length]:
                tmp_max_length += 1
                i += length

            #compares sequence with previous sequence
            if tmp_max_length > max_length:
                #replaces it into the final sequence length
                max_length = tmp_max_length
    #stores the sequences into the dictionary
    sequence[key] += max_length
    
#Open database of every person and compare to STR
with open(argv[1]) as cvs_file:
    people = DictReader(cvs_file)
    for match in people:
        count = 0
        #compares the sequences to every people
        #if there is a match, print out name
        for dna in sequence:
            if sequence[dna] == int(match[dna]):
                count += 1
        if count == len(sequence):
            print(match['name'])
            exit()
    #else, print there is not match
    print("No match")