# 🎯 The Twin Occurrence Quest

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)
</div>

---

## 📋 Problem Description

Harry and Sondos challenge you with a puzzle to help sharpen your skills before the contest. You are given a **sorted array A**. In this array, some numbers can appear more than once.

You will receive some queries. For each query, your task is to search for a specified number **X** and determine both its **first** and **last** occurrence in the array.

> **Important:** Report your answer using **1-indexed positions**. If **X** is not found, output `-1 -1`.

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `N Q` | Two space-separated integers: number of elements and number of queries |
| 2 | `A₁ A₂ ... Aₙ` | N space-separated integers representing the sorted array |
| 3 to Q+2 | `Xⱼ` | Single integer per line: the number to search for |

**Example Structure:**
```
N Q
A₁ A₂ A₃ ... Aₙ
X₁
X₂
...
Xᵩ
```

---

## 📤 Output Format

For each query, output **one line** containing two space-separated integers:

- ✅ If **X** is found: `first_position last_position` (1-indexed)
- ❌ If **X** is not found: `-1 -1`

---

## 🔒 Constraints
```
1 ≤ N, Q ≤ 10⁵
Aᵢ ≤ Aᵢ₊₁ (array is sorted in non-decreasing order)
|Aᵢ| ≤ 10⁹ for all i = 1, ..., N
|Xⱼ| ≤ 10⁹ for all j = 1, ..., Q
```

### ⏱️ Time and Memory Limits

- **Time limit:** 2500 ms
- **Memory limit:** 256 MB

---

## 💡 Sample Test Case

### Input
```
8 4
2 4 4 4 5 8 10 12
4
10
5
11
```

### Output
```
2 4
7 7
5 5
-1 -1
```

### 📊 Explanation

**Array (1-indexed):** `[2, 4, 4, 4, 5, 8, 10, 12]`

| Query | X | Result | Explanation |
|-------|---|--------|-------------|
| 1 | 4 | `2 4` | First occurrence at index 2, last at index 4 |
| 2 | 10 | `7 7` | Single occurrence at index 7 |
| 3 | 5 | `5 5` | Single occurrence at index 5 |
| 4 | 11 | `-1 -1` | Not found in array |

---

## 🎓 Solution Approach

### Algorithm Strategy

This problem is efficiently solved using **Binary Search**:

1. **Find First Occurrence**
   - Use binary search to find the leftmost position where X appears
   - Modify binary search to continue searching left even after finding X

2. **Find Last Occurrence**
   - Use binary search to find the rightmost position where X appears
   - Modify binary search to continue searching right even after finding X

3. **Handle Not Found Case**
   - If first occurrence not found, return `-1 -1`
   - Validate that the element at found position equals X

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(Q × log N) |
| **Space** | O(N) |

**Where:**
- Q = number of queries
- N = size of array

---

## 🔑 Key Insights

- ✨ Array is **pre-sorted** - exploit this with binary search
- ✨ Multiple occurrences form a **contiguous block**
- ✨ Use **modified binary search** for O(log N) per query
- ✨ Remember **1-indexed** output requirement
- ✨ Edge cases: element not found, single occurrence, all elements same

---

## 📚 Related Topics

- Binary Search
- Array Manipulation
- Lower Bound / Upper Bound
- Sorted Arrays
- Range Queries

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>