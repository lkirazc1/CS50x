# TODO
from cs50 import get_string
# get input for phrase
phrase = get_string("Text: ")
# count letters
letters = 0
for i in phrase:
    if i.isalpha():
        letters += 1
# count words
words = 1

for i in phrase:
    if i == ' ':
        words += 1

# get L
L = (letters / words) * 100

# count sentences
sentences = 0

for i in phrase:
    if i in ['.', '!', '?']:
        sentences += 1
# get S

S = sentences / words * 100
# get index
index = 0.0588 * L - 0.296 * S - 15.8


# output final reading level

if index > 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print("Grade", int(round(index, 0)))