from cs50 import get_string
from cs50 import get_int
import math

def check_sum(num):
    # variables
    digit = 0
    k = 0
    s = 0
    sum = 0
    
    while (num > 0):
        digit = int(num % 10)
        # test print("Digit: "+ str(digit))
        num = int(num / 10)
        # test print("num: " + str(num))
        k += 1
        # test print("k: " + str(k))

        if (k % 2 == 0):
            if (digit * 2 >= 10):
                s = digit * 2 - 9
                # test print("even digit: " + str(s))
            else:
                s = digit * 2
                # test print("even single digit: " + str(s))
        
        else:
            s = digit
            # test print("odd digit: " +str(s))
            
        sum = sum + s

    # check to see if sum is even. If it is, return 1 to signify it passes luhn's algorithim
    if (sum % 10 == 0):
        return 1
        
    else:
        return 0
        

# get cc number from user 
num = get_int("Number: ")

# put number through luhn's algorithim
check_sum(num)

# if passes luhns algorithim, determine if it is a VISA, MASTER, or AMEX
if (check_sum(num) == 1):
    if ((num >= 4000000000000 and num <= 4999999999999) or (num >= 4000000000000000 and num <= 4999999999999999)):
        print("VISA")
        print("")
    elif (num >= 340000000000000 and num <= 379999999999999):
        print("AMEX")
        print("")
    elif (num >= 5100000000000000 and num <= 5599999999999999):
        print("MASTERCARD")
        print("")


else:
    print("INVALID")