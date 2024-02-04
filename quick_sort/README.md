# Quick Sort

Quick Sort is a divide and conquer algorithm that picks an element as a pivot
and divides into two sub-arrays with smaller and larger elements than the pivot,
sorting them recursively.

The Hoare partition method can be used to improve performance since it performs
less swaps compared to the *\*normal\** partitioning method.

## Example

![Merge Sort Example](https://upload.wikimedia.org/wikipedia/commons/thumb/6/6a/Sorting_quicksort_anim.gif/220px-Sorting_quicksort_anim.gif)

## Complexity

**Space complexity:** O(n)

**Time complexity:**

|    Best    |   Average   |    Worst    |
|:----------:|:-----------:|:-----------:|
| O(nlog(n)) | O(nlog(n))  | O(n^2)      |
