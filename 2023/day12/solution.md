# My Solution

## Part I

- backtracking: every '?' can be replaced by either '#' or '.'
- try every combination (brute force)

## Part II

Some idea:
- leading '.' and trailing '.' can be removed
- several '.' in the middle can be reduced to 1 only.
- 1,1,3 => #.#.###

## Part Ibis and II

- Do it recursively
- Move by the block of damaged springs
- Use cache to save states


