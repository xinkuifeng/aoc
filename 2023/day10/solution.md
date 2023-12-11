# My Solution

## Part I

- Need to figure out how to move from one pipe to the next taking account the current
  head direction.
- Use BFS to find the farthest point.

## Part II

- Identify the main loop.
- Can go two directions.
- For each direction, move along the loop till back to the start position.
- Note that the board has 3 parts: the main loop, the area in the loop, and outside.
- Count the tiles on the left hand side and on the right hand side as you move forward.
- Flood fill the outside and the inside areas.

