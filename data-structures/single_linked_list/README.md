# Single Linked List

A Single Linked List is a data structure that consists of a sequence of
elements in which every element has a link to the next element in the sequence.

![Single Linked List Example](/assets/single-linked-list.png)

Another type of linked list is the [double linked list](/data-structures/double-linked-list/README.md),
which is also talked about in this repository.

## Operations

### Insertion

To insert an element in a single linked list is needed to create a
new node with the given value and link the previous node to the new node.

The insertion is O(1) because we can insert a new node at any position in the
list without needing to iterate over the list, having only a node reference.


### Deletion

To delete an element in a single linked list is needed to find the
previous node of the node to be deleted and link it to the next node.

The deletion is O(n) because to delete a node, we need to iterate over the
list to find the previous node to update it's next reference.

We can remove the next node of a given node in O(1).

### Access

To access an element in a single linked list is needed to iterate
over the list until the desired position is reached.

### Search

To search an element in a single linked list is needed to iterate
over the list and compare the value of each node with the given value,
iterating over all the nodes in the list if the element is not found.

## Time Complexity

|  Operation  |   Average   |
|:-----------:|:-----------:|
| Insertion   | O(1)        |
| Deletion    | O(n)        |
| Access      | O(n)        |
| Search      | O(n)        |
