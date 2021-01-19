from cs50 import SQL
from csv import reader
from sys import argv

# check for correct command line argv
if (len(argv) != 2):
    print("Usage: roster.py house")
    exit()

# open database
db = SQL("sqlite:///students.db")
# list all info alphabetically by last name, accepting user's house input
student_info = db.execute("SELECT * FROM students WHERE house = (?) ORDER BY last", argv[1])
# test print (student_info)

# print out info in order of first name, last name, and birth year
for student in student_info:
    if (student['middle'] == None):
        print(student['first'] + " " + student['last'] + ", " "born " + str(student['birth']))
    else:
        print(student['first'] + " " + student['middle'] + " " + student['last'] + ", " "born " + str(student['birth']))
