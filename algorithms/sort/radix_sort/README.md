# Radix Sort

Radix sort is a linear sorting algorithm, sorting elements digit by digit,
using a stable sorting algorithm (in this implementation,
[counting sort](/algorithms/sort/counting_sort/README.md)).

## Example

![Radix Sort Example](https://www.simplilearn.com/ice9/free_resources_article_thumb/Radix-Sort-Soni/what-is-radix-sort-algorithm.png)

## Complexity

Being `k` the biggest key in the array,

**Space complexity:** O(n + k)

**Time complexity:**

|     Best     |   Average   |    Worst    |
|:------------:|:-----------:|:-----------:|
| O(n * k)     | O(n * k)    | O(n * k)    |
