# My Solution

Preparation:
- Scan the input line by line
- For each digit, mark its coordinates `(x, y)`. Link `(x, y)` to the index of the number.
- Push the numbers to a vector.
- For each symbol, push its coordinates `(x, y)` to another vector.

Solve:
- Iterate through the points of the symbols one by one.
- Find all the digits adjacent to the symbol.
- Push the indice of the corresponding numbers to a set.
- Compute the sum.
