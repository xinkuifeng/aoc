# My Solution

- use priority_queue to sort the hands. put the weakest hand at the front.
- define a custom rule to sort the queue:
    - first order by type
    - then order by card
- The types:
    - Five of a kind: easy
    - Four of a kind: easy
    - Full house / Three of a kind: treaky
    - Two pair: easy
    - One pair: easy
    - High card: 0 pair

