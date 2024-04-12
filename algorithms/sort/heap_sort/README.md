# Heap Sort

Heap sort is a comparison-based sorting algorithm similar to
[selection sort](/algorithms/sort/selection_sort), but using a
more appropriate data structure.

Heap sort divides the input in a sorted and unsorted region, extracting elements
of the unsorted region and adding them to the sorted region. The improvement
comparing to selection sort is the use of a [Heap](/data-structures/heap),
which has all its elements sorted and has O(1) complexity for finding
the minimum element (compared to O(n) in a linear-time search data structure).

## Example

![Heap Sort Example](https://upload.wikimedia.org/wikipedia/commons/1/1b/Sorting_heapsort_anim.gif)

## Complexity

**Space complexity:** O(1)

**Time complexity:**

|     Best     |   Average   |    Worst    |
|:------------:|:-----------:|:-----------:|
| O(nlog(n))   | O(nlog(n))  | O(nlog(n))  |
