# My Solution

## Simplified version

- From each starting point, compute how many steps it would take to reach the (first)
  end position.
- The Least Common Multiple of those steps is the answer.

## Longer version

- From each starting point, run a full loop. Note how many end positions can be reached and
  how many steps it would take.
    - Full loop: you go back to a node you were before and the set of direction is the same.
- Find the min of all the possible LCMs.

