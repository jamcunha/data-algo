# Bucket Sort

Bucket sort is a linear sorting algorithm that works by distributing
array elements by a defined number of buckets, sorting the buckets individualy
and concatenating all buckets after sorting.

## Example

![Bucket Sort Example](https://www.programiz.com/sites/tutorial2program/files/Bucket_2.png)

## Complexity

Being `k` the number of buckets,

**Space complexity:** O(n)

**Time complexity:**

|     Best     |   Average   |    Worst    |
|:------------:|:-----------:|:-----------:|
| O(n + k)     | O(n + k)    | O(n^2)      |
