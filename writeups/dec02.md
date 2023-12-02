# Day 2: Cube Conundrum

### Description

As input, we are given a sequence of games where each game composes of a number of
rounds. In each round a handful of cubes are pulled from the  bag and the count of each
color is recorded. The format of a line is:
`Game 1: 12 blue, 15 red, 2 green; 17 red, 8 green, 5 blue; 8 red, 17 blue; 9 green, 1 blue, 4 red`

The goal of Part 1 is to determine the sum of game ids whose  bag possibly contains
fewer than:
 - 12 reds
 - 13 greens
 - 14 blues

The goal of part 2 is to determine the sum of the "power" of each game. "power" is
defined to be the product of the minimum possible # of cubes of each color.

### Solution

I wrote a parser to parse a game line into the following object:
```json
{
  "id": "number",
  "max_red": "number",
  "max_green": "number",
  "max_blue": "number"
}
```

For part 1, I used this parser to:
```
possible_sum = 0
for line in input:
  game = parse_game(line)
  if game.possible():
    possible_sum += game.id
```

where `possible()` is:
```
def possible(game):
  return game.max_red <= 12 and game.max_green <= 13 and game.max_blue <= 14
```

For part 2, I ussed this parser to:
```
power_sum = 0
possible_sum = 0
for line in input:
  power_sum += parse_game(line).power()
```

where `power()` is:
```
def power(game):
  return game.max_red * game.max_green * game.max_blue
```
