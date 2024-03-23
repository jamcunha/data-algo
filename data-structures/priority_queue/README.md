# Priority Queue

A Priority Queue is similar to a regular [Queue](TODO), having a priority
associated with each element where, in case of a Min-Priority Queue, the
element with the least priority is served first.

The Priority Queue impelemented is based on a Heap, but it can be implemented
with other data structures, for example a BST.

## Operations

### Insertion and Deletion

Insertion and Deletion in a Priority Queue is similar to a [Heap](/data-structures/heap/README.md)
with the only difference in heapifying based on the priority.

### Peek

The peek operation is used to check the element with the least or greatest priority
with O(1) complexity.

### Update Key

Priority Queues also add a new operation, the decrease key or increase key,
based if it's a Min-Priority Queue or a Max-Priority Queue respectively.

## Time Complexity

|  Operation  |   Average   |
|:-----------:|:-----------:|
| Insertion   | O(log(n))   |
| Deletion    | O(log(n))   |
| Peek        | O(1)        |
| Update Key  | O(log(n))   |
