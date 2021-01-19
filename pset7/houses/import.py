from cs50 import SQL
from csv import reader
from sys import argv

#check to see if correct command line arg
if len(argv) != 2:
    print ("Usage: import.py characters.csv")
    exit()

# open database
db = SQL("sqlite:///students.db")

# open up characters csv file and transfer student's info into a list 
with open(argv[1]) as csv_file:
    characters = reader(csv_file)
    for info in characters:
        if info[0] == 'name':
            continue
        
        # split full name into first, middle, last
        full_name = info[0].split(" ")
        # test print(full_name)
        if len(full_name) == 3:
            # test print (str(full_name) + str(full_name[1]))
            # insert names into table of first, middle, and last name
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?,?,?,?,?)", full_name[0], full_name[1], full_name[2], info[1], info[2])
        else:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?,?,?,?,?)", full_name[0], None, full_name[1], info[1], info[2])
            
