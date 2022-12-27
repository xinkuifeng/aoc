# Reflect

## Opt 1

This problem can be (intuitively) solved by using `unordered_set` and `queue`:
- use the hash set to keep the already seen characters;
- also put those chars to the queue.

When a new char arrives, if it has already been seen, `pop` this char and
all the chars before it out of the queue. Then `push` this new char into the queue.

When the size of the queue reaches to the target number, compute the final result.

## Opt 2 (Selected)

Use `vector` to keep the index of the chars. Initialize this vector (from a..z) to -1.

Use a local variable `start` to mark the start of packet (message). When a new char arrives,
if its last known index is larger than or equal to `start`, it means this char has
already been seen. In this case, reset `start` to `last_known_index + 1` which means all
the chars that are before `last_known_index` (inclusive) are forgotten.

This method reduces the time complexity of repositioning the front of the queue from O(n) to O(1).
