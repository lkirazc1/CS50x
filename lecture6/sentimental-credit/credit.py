# TODO
from cs50 import get_int

# make reversed list


def make_list(num):
    list = []
    while num > 0:
        list.append(num % 10)
        num //= 10
    return list

# reverse a list


def reverse_list(list):
    return list[::-1]

# solve list


def solve(list):
    sum = 0
    for i in list[1::2]:
        sum += i * 2 % 10
        if i * 2 > 9:
            sum += 1
    for i in list[::2]:
        sum += i
    if sum % 10 == 0:
        return True
    return False


# get user input
num = get_int("Number: ")
# check if input is valid using functions
valid = solve(make_list(num))
output = False
# make list to check which type of card
buffer_list = reverse_list(make_list(num))
digits = len(buffer_list)
if valid:
    if digits == 16:
        if buffer_list[0] == 4:
            output = True
            print("VISA")
        if buffer_list[0] == 5:
            if buffer_list[1] in range(1, 6):
                output = True
                print("MASTERCARD")

    if digits == 15:
        if buffer_list[0] == 3:
            if buffer_list[1] in [4, 7]:
                output = True
                print("AMEX")

    if digits == 13:
        if buffer_list[0] == 4:
            output = True
            print("VISA")
if not valid or not output:
    print("INVALID")