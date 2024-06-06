# Red-Black Tree

A red-black tree is a [binary search tree](/data-structures/binary_search_tree)
where each node as a extra bit to store the color of the node, either red or black.

The objective of a red-black tree is to keep the tree balanced, ensuring that the
height of the tree is O(log n), where n is the number of nodes in the tree.

![Red-Black Tree Example](/assets/rb-tree.png)

## Properties

- Each node is either red or black.
- The root node is always black.
- All leaves (NIL) are black.
- If a red node has children, then the children are black.
- Every path from a node to its descendant NIL nodes must have the same number of black nodes.

> [!IMPORTANT]
> Red-Black trees, despite following each property, may not be perfectly balanced.
> <img src="/assets/unbalanced-rb-tree.png" alt="Red-Black Tree Example" width="400"/>

## Operations

### Insert

Insertion is initially done in a simmilar manner to a binary search tree,
with the new node being inserted as a red node.

After insertion, we need to check if the tree is still balanced, checking 4 cases:

> [!NOTE]
> Cases 2 and 3 are done for a parent node that is a left child.
> For a parent node that is a right child, cases are mirrorred.

#### Case 1 - Node uncle is red

If the uncle node is red, we can simply recolor the parent and uncle nodes to black,
and the grandparent node to red, then move the problem up to the grandparent node.

#### Case 2 - Node uncle is black and node is a right child

If the uncle node is black and the new node is a right child, we can rotate
the parent node to the left, and then proceed to case 3 with the parent as the new node.

#### Case 3 - Node uncle is black and node is a left child

If the uncle node is black and the new node is a left child, we can recolor the parent node to black,
the grandparent node to red, and rotate the grandparent node to the right.

### Delete

Deletion is initially done in a simmilar manner to a binary search tree, with
the node being deleted and replaced by its child, with the caveat of storing the reference
to the sibling node of the deleted node to be used later in the balancing process.

After deletion, we need to check if the tree is still balanced, checking 4 cases:

> [!NOTE]
> All cases are done for a left child, for a right child, cases are mirrorred.

#### Case 1 - Node sibling is red

When the sibling node is red, the node is recolored to black, the parent node to red,
and the parent node is rotated to the left.

#### Case 2 - Node sibling is black and both sibling children are black

When the sibling node is black and both its children are black,
the sibling node is recolored to red and the parent node is moved up to the balancing process.

#### Case 3 - Node sibling is black and sibling left child is red

When the sibling node is black and its left child is red,
the sibling node left child is recolored to black, the sibling node to red,
and the sibling node is rotated to the right.

#### Case 4 - Node sibling is black and sibling right child is red

When the sibling node is black and its right child is red,
the sibling node is recolored to the parent node color, the parent node to black,
the sibling node right child to black, and the parent node is rotated to the left.

### Search and Access

Search and access operations are the same as in a binary search tree.

## Complexity

| Operation |   Average   |   Worst   |
|:---------:|:-----------:|:---------:|
| Insertion | O(log n)    | O(log n)  |
| Deletion  | O(log n)    | O(log n)  |
| Search    | O(log n)    | O(log n)  |
| Access    | O(log n)    | O(log n)  |
