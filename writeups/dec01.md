# Day 1: Trebuchet?!

### Description

We are given a text file where each line is an amended "calibration value". To recover
the original value we need to find the first number and the last number in each value.

Basically we need to match:
```python3
[a-z]*[0-9]([a-z]*[0-9])*
```

and extract the first and last `[0-9]` groups (which may be the same).

Example:
```
nine32five3six -> 33
```

### Part 1

My solution was pretty straigt forward:
```plaintext
let first, last
let sawFirst = false
foreach ch in line:
  if isdigit(ch):
    if !sawFirst: first = ch
    last = ch
    sawFirst = true
assert sawFirst
first -= '0'
last -= '0'
display first * 10 + last
```

### Part 2

For the second part of day one, a challenge was added. Notice in the above example,
`33` is not really the combination of the first and last numbers. The first number is
"nine" and the last number is "six". The goal of part 2 is to handle this new criteria
of accepting what I called "english numbers".

My solution to this was insted of marching through the line once, I would first start
at the beginning and walk forward until I matched a digit or an "english number" and
then I would repeat starting at the end and walking backwards. My solution looks like:

```plaintext
fun english_number(st):
  // where safe_index_of does a strncmp
  return ["zero", "one", ..., "nine"].safe_index_of(st)

fun get_first_digit(line):
  ptr = line.start()
  while ptr <= line.end():
    if isdigit(*ptr): return *ptr - '0'
    if en := english_number(ptr): return en
    ptr++

fun get_last_digit(line):
  ptr = line.end()
  while ptr >= line.start():
    if isdigit(*ptr): return *ptr - '0'
    if en := english_number(ptr): return en
    ptr--

let first = get_first_digit(line)
let last = get_last_digit(line)
display first * 10 + last
```