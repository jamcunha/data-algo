# AVL Tree

An AVL tree is a self-balancing [binary search tree](/data-structures/binary-search-tree)
that maintains a height difference of at most 1 between its left and right subtrees.

To self balance, an AVL tree performs rotations on nodes during insertion and deletion
in order to maintain the height difference constraint.

## Balancing

After an insertion or deletion operation, the AVL tree may become unbalanced. To
rebalance the tree, the AVL tree performs one of four rotations:

> [!NOTE]
> This cases are for an unbalanced node where the left subtree is heavier than
> the right subtree. The cases are mirrored for an unbalanced node where the
> right subtree is heavier than the left subtree.

### Case 1: When the left subtree is unbalanced and the left child of the left subtree is either balanced or left-heavy

When the left subtree is unbalanced and the left child of the left subtree is
either balanced or left-heavy, the AVL tree performs a right rotation.

### Case 2: When the left subtree is unbalanced and the right child of the left subtree is right-heavy

When the left subtree is unbalanced and the right child of the left subtree is
right-heavy, the AVL tree performs a left-right rotation on the left subtree,
followed by a right rotation on the unbalanced node.

## Operations

### Insert

An insertion operation in an AVL tree is the same as in a binary search tree,
with the addition of rebalancing the tree after the insertion.

### Delete

A delete operation in an AVL tree is the same as in a binary search tree,
with the addition of rebalancing the tree after the deletion.

### Search and Access

Search and access operations are the same as in a binary search tree.

## Complexity

| Operation |   Average   |   Worst   |
|:---------:|:-----------:|:---------:|
| Insertion | O(log n)    | O(log n)  |
| Deletion  | O(log n)    | O(log n)  |
| Search    | O(log n)    | O(log n)  |
| Access    | O(log n)    | O(log n)  |
