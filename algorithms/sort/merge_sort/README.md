# Merge Sort

Merge Sort is an efficient sorting algorithm consisting on the principle of
Divide and Conquer where a list is divided into multiple sublists with
a single element and merging those in a way that results in a sorted list.

The time complexity of merge sort is explained by having 2 steps,
the division of the list, making the height of the recursion tree log2(n) + 1
***(aprox log(n))***, and the merging of two sublists where in the last merge
the two sublists length combined is the length of the original list, making it O(n).

## Example

![Merge Sort Example](https://upload.wikimedia.org/wikipedia/commons/thumb/c/cc/Merge-sort-example-300px.gif/220px-Merge-sort-example-300px.gif)

#### A break-down of the steps in a merge sort

![Merge Sort Steps](https://upload.wikimedia.org/wikipedia/commons/thumb/e/e6/Merge_sort_algorithm_diagram.svg/300px-Merge_sort_algorithm_diagram.svg.png)

## Complexity

**Space complexity:** O(n)

**Time complexity:**

|    Best    |   Average   |    Worst    |
|:----------:|:-----------:|:-----------:|
| O(nlog(n)) | O(nlog(n))  | O(nlog(n))  |
