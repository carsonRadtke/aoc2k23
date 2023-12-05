# Scratchcards

Similar to day 2, we are given an human-ish input. Each line in the input is of the form
`Game ([0-9]+): ([0-9]+\s+)+ | ([0-9]+\s+)+`

Where
 - Group 0: game id
 - Group 1: winning numbers
 - Group 2: numbers

## Part 1:

The score of a scratch card is `2**(n-1)` where `n` is the number of winning numbers you
have.

Pretty straightforward, I noticed that there were always 10 winning numbers and 25
number numbers, so I create an `int[10]` and `int[25]` then check for intersction.

## Part 2:

We find out the real rules are for every winning number, you win copies of subsequent 
scratch cards. 

This is also straightforward. I first compute the number of winning numbers and then
loop back through all winning numbers and multiple the subsequenct scratch cards with
the necessary number of total wins.


Pseudocode:
```plaintext
scratches = [1 for x in line_count]
for idx, line in enumerate(lines):
  matches = line.total_wins()
  for i in range(matches):
    scratches[idx + i + 1] += scratches[idx]
display sum(scratches)
```
