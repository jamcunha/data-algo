# Binary Search Tree

A Binary Search Tree (BST) is a data structure used to store data in a sorted manner.
Each node of a binary tree has a left child and a right child, as well as it's parent node.

The left child is always of a value less than the parent node,
and the right child is always of a value greater than the parent node.

BSTs allow for faster searching, insertion, and deletion of data,
since it's layout allow comparison that skips half of the remaining tree at each step.

The performance of a BST is dependent on the balance of the tree.
When unbalanced, the tree can degrade to a linked list, which would make the performance linear.

To solve this issue, there are self-balancing trees, such as [AVL](TODO) and [Red-Black trees](TODO).

![Binary Search Tree](/assets/bst.png)

## Operations

### Insertion

To insert a new node in a BST, we start at the root node and compare the value
of the new node with the current node recursively until we find a leaf node.
Then we insert the new node as the left child if the value is less than the current node,
or as the right child if the value is greater.

### Deletion

To delete a node from a BST, we first need to find the node.
If the node has no children, we can simply remove it.
If the node has one child, we can replace the node with its child.
If the node has two children, we can replace the node with the smallest node in the right subtree,
moving the successor node's child to the successor's position.

### Searching

To search for a value in a BST, we start at the root node and compare the value
with the current node recursively until we find the value or a leaf node.

### Access

Accessing a node in a BST is similar to searching, but instead of returning a boolean,
we return the node itself.

## Traversal

### In-order

In-order traversal of a BST visits the nodes in ascending order.

![In-order Traversal](/assets/inorder.png)

### Pre-order

Pre-order traversal of a BST visits the root node first, then the left subtree, and finally the right subtree.

![Pre-order Traversal](/assets/preorder.png)

### Post-order

Post-order traversal of a BST visits the left subtree, then the right subtree, and finally the root node.

![Post-order Traversal](/assets/postorder.png)

## Complexity

The average time complexity of a BST is O(log n) for insertion, deletion, search, and access,
with log(n) being the height of a balaced tree. The worst case scenario is O(n) for all operations,
when the tree is unbalanced.

| Operation |   Average   |   Worst   |
|:---------:|:-----------:|:---------:|
| Insertion | O(log n)    | O(n)      |
| Deletion  | O(log n)    | O(n)      |
| Search    | O(log n)    | O(n)      |
| Access    | O(log n)    | O(n)      |
