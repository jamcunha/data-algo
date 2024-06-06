# Double Linked List

A double linked list is similar to a [single linked list](/data-structures/single-linked-list),
with the difference that each node has one more link to the previous node.

![Double Linked List Example](/assets/double-linked-list.png)

## Operations

All operations in a double linked list are similar to the operations in a
single linked list, all having the same time complexity but one.

Thanks to the previous reference in each node, the **deletion** operation can
be done in O(1) time complexity since we can update the previous node reference
to the next node reference without needing to iterate over the list.

## Time Complexity

|  Operation  |   Average   |
|:-----------:|:-----------:|
| Insertion   | O(1)        |
| Deletion    | O(1)        |
| Access      | O(n)        |
| Search      | O(n)        |
