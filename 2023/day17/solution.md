# My Solution

## Part I

- cannot use BFS or DFS to find the optimal solution: too many states.
- Use Dijkstra's algorithm for path finding.

```
- use the priority queue and keep the min value (heat loss) at the top.
- once the end position is reached, it's the optimal solution.
- skip the already visited point.
- pick the point with the smallest heat loss, process its possible neighbors then enqueue.
- finally mark the current point as visited.
```

- Make a super point: position + head direction + times of that direction
- Track the super point as visited or not visit.

## Part II

- As one direction is started, it requires 4 moves to change the direction.
  Start in the two directions: 'v' + '>'

