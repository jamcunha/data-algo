# Interval Tree

> [!NOTE]
> **The interval tree implementation is just a rough sketch since I just wanted
> to experiment with the concept. May revisit it later.**
>
> **Note to self:** Deletion could also be done by interval, which may be O(k + log n).

An interval tree is a data structure that allows efficient searching for a set of intervals
that contain or overlap a given point or interval.

For an easy understanding, think of an interval tree as a schedule and the
nodes as events. The tree allows you to find all events that are happening
at a given time.

This data structure can be implemented using a variety of tree structures,
such as [binary search trees](../binary_search_tree), [AVL trees](../avl_tree),
or [red-black trees](../rb_tree), which are augmented to store additional information
about the intervals.

For the sake of simplicity, this implementation uses a binary search tree
to implement the interval tree.

![Interval Tree Example](https://upload.wikimedia.org/wikipedia/en/b/b0/Example_of_augmented_tree_with_low_value_as_the_key_and_maximum_high_as_extra_annotation.png)

## Operations

The operations of an interval tree are similar to those of the tree used to implement it,
with the caveat that the tree is augmented to store additional information about the intervals.

> [!NOTE]
> In the implementation provided, the tree only works with the interval,
> making it unable to delete or search for an element since an identifier
> is needed to do so.

### Search & Delete

The search and delete operations perform a search for the identifier of the element,
and then perform the operation on the element found.

### Insert

The insert operation is similar to the operation of the tree used to implement
the interval tree, but we sort the tree by the provided interval.

The interval is added to the left of a node in case of the lower bound being
lower than the node's interval lower bound, else it is added to the right.

The maximum upper bound of the interval is calculated and stored in the node
to allow for efficient searching of intervals that contain or overlap a
given point or interval.

### Search Interval

The search interval operation searches for all intervals that contain or overlap
a given interval.

For each node, if the left child maximum upper bound is greater than the lower
bound of the interval, the left child is searched, else the right child is searched.

If the node's interval overlaps the given interval, the node is added to the result.

### Search Point

This operations is similar to the search interval operation, but instead of
searching for intervals that contain or overlap a given interval, it searches
for intervals that contain a given point.

All intervals that contains the given point overlap, and the node's left child
interval maximum upper bound is checked to see if it is greater than the point.

## Complexity

Since the search and deletion operations find the element by an identifier,
the complexity of these operations is O(n) since the tree is not optimized
for these operations.

The complexity of the operations regarding intervals are the same as the
operations of the tree used to implement the interval tree, having the search
operations a complexity of O(k + log n), with k being all the intervals found.
If we only find the first interval, the complexity is the same as a search in
the tree used to implement the interval tree.

|     Operation     |   Average   |   Worst   |
|:-----------------:|:-----------:|:---------:|
| Insertion         | O(log n)    | O(n)      |
| Search Interval   | O(k + log n)| O(n)      |
| Search Point      | O(k + log n)| O(n)      |
