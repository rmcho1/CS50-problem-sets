from cs50 import get_string
from cs50 import get_int

# get height
height = get_int("Height: ")

# prompts user to input a number between 0 to 9 until user inputs number within that range
while (height < 1 or height > 8):
    height = get_int("Height: ")
    if (height >= 1 and height <= 8):
        break
    
# once input is between 0 to 9, it will create mario columns
if (height >= 1 and height <= 8):
    
    for x in range(height):
        # create loop for white spaces on side of # that starts from x until height -1
        for y in range(x, height-1):
            # print white spaces on left side of #
            print(" ", end='')
        # create loop for hashtags, where it prints out x+1 hashtags per row
        for z in range(x + 1):
            #print # x+1 amount for each row 
            print("#", end ='')
         # add two spaces before reflecting # for each row
        print("  ", end='')
    # create loop that reflects left side of #
        for w in range(x + 1):
            print("#", end='')
    # Creates a new line
        print("")
        