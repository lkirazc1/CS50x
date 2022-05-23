# TODO
from cs50 import get_int
height = get_int("Height: ")
# make sure height is between 1 and 8 inclusive
while height > 8 or height < 1:
    height = get_int("Height: ")

for i in range(1, height + 1):
    # print spaces at the beginning
    for j in range(height - i):
        print(" ", end="")
    # print hashes at the beginning
    for k in range(i):
        print("#", end="")
    # print space in middle
    print("  ", end="")
    # print final hashes
    for x in range(i):
        print("#", end="")
    # print ending whitespace and new line
    print()