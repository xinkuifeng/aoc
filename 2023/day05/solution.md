# My Solution

Key takeaways:
- Use a queue to keep the segments that cannot be moved by the current line.
- Find the minimum segment that can be mapped. Move it to the next round directly.
- current_seg - moved_seg are the remaining parts. Put them back for the next line.

