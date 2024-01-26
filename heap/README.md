# Heap

> **Note:** This is focused on Binary Heaps

Heap is a specialized tree-based data structure (the implemented heap can be
viewed as a nearly complete binary tree) that satisfies the heap property.

## Types of Binary Heaps

Binary Heaps can be of two types, Min-Heap and Max-Heap.

### Min-Heap

A Min-Heap is a type of Binary Heap where the minimum element of the heap is
always on top (root). For every node of a Min-Heap, if a node is parent of
other then the value of the node needs to be less or equal to the value of its child.

#### Example of a Min-Heap

![Example of a Min-Heap](/assets/min-heap.png)

### Max-Heap

A Max-Heap is a type of Binary Heap where the maximum element of the heap is
always on top (root). For every node of a Max-Heap, if a node is parent of
other then the value of the node needs to be greater or equal to the value of its child.

#### Example of a Max-Heap

![Example of a Max-Heap](/assets/max-heap.png)

## Operations

### Insertion

To insert a new item in the Binary Heap, place it in the next available position
and heapify it by swapping the element with its parent until the heap is restored.

### Deletion

In a Binary Heap, we can pop the root element, placing the last element in its
position and heapify the new root until the heap is restored.

### Heapify

Heapify is the process of maintaining the heap property. It can be used to
heapify starting from a leaf until the root (heapify up) or starting from the
root (heapify down).

## Time Complexity

|  Operation  |   Average   |
|:-----------:|:-----------:|
| Insertion   | O(log(n))   |
| Deletion    | O(log(n))   |
| Heapify     | O(log(n))   |

## A Final Note

I tried to implement a generic heap, for it to be either a Min-Heap or a Max-Heap
depending on the `compare` function given in it's creation.

```c
// If you want a Min-Heap
bool min_heap(int a, int b) {
    return a < b;
}

// If you want a Max-Heap
bool max_heap(int a, int b) {
    return a > b;
}
```
