# Day 3: Gear Ratios

As input we recieve a matrix of characters (numbers and special characters). Each number
in the matrix is a part number if and only if it touches a special character.

## Part 1

### Compute the sum of all part numbers in the schematic.

This is pretty straight forward:
 1. find all numbers
 2. walk the perimeter to see if there is a special character.


## Part 2

We learned of a mistake in our understanding of the schematic. We found out that if
exactly two part numbers are adjacent to a single '*', then that represents a gear
ratio. Our task is now to add up all the gear ratios.

### Compute the sum of all gear ratios

This is also pretty straight forward
  1. find all '*'
  2. walk the permeter looking for numbers

  