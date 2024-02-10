# Counting Sort

Counting sort is an integer sorting algorithm used to sort a collection of
objects according to keys that are small posivite integers.

Counting sort works by counting the number of objects that have each distinct
key value, and using arithmetic on those counts to determine the positions of
each key value in the output sequence.

## Example

![Counting Sort Example](https://atechdaily.com/resources/images/posts/2020/5/375/countingsort.gif)

![Counting Sort Example 2](https://www.programiz.com/sites/tutorial2program/files/Counting-sort-4_1.png)

## Complexity

Being `k` the biggest number in the array,

**Space complexity:** O(n + k)

**Time complexity:**

|     Best     |   Average   |    Worst    |
|:------------:|:-----------:|:-----------:|
| O(n + k)     | O(n + k)    | O(n + k)    |
