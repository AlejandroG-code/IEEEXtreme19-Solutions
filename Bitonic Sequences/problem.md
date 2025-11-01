# 🔢 Bitonic Sequences

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

We define a **positive bitonic sequence** of sum **N** as a sequence of positive integers **S₁, S₂, ..., Sₖ** such that:

- The sum equals N: **∑ᵢ₌₁ᵏ Sᵢ = N**
- There exists an index **j** satisfying:
  - **Sᵢ ≤ Sᵢ₊₁** for all **1 ≤ i < j**, and
  - **Sⱼ ≥ Sⱼ₊₁** for all **j ≤ i < k**

In other words, the sequence is **non-decreasing** up to some point, then **non-increasing** after that point.

Find the number of distinct positive bitonic sequences with total sum **N**, for all **1 ≤ N ≤ M**, modulo **10⁹ + 7**.

Two bitonic sequences **S₁** and **S₂** are considered different if they have different lengths, or if there exists an index **j'** such that **S₁,ⱼ' ≠ S₂,ⱼ'**.

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `M` | Single integer representing the maximum sum |

**Example Structure:**
```
M
```

---

## 📤 Output Format

Print the number of distinct positive bitonic sequences for each **N (1 ≤ N ≤ M)**, modulo **10⁹ + 7**.

---

## 🔒 Constraints
```
1 ≤ M ≤ 3 × 10⁵
```

### ⏱️ Time and Memory Limits

- **Time limit:** 5000 ms
- **Memory limit:** 128 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This problem requires **dynamic programming** and **combinatorics**:

1. **Understanding Bitonic Sequences**
   - Sequence increases to a peak, then decreases
   - Peak can be at any position (including start or end)
   - Single element sequences are valid (both increasing and decreasing)

2. **Dynamic Programming Approach**
   - Use DP to count sequences by sum and maximum element
   - Consider partitions of N into increasing/decreasing parts
   - Combine increasing and decreasing subsequences at the peak

3. **Optimization**
   - Precompute partition counts
   - Use memoization to avoid redundant calculations
   - Apply modular arithmetic throughout

4. **Special Cases**
   - Single element: {N} is always valid
   - Two elements: {a, b} where a + b = N
   - Monotonic sequences (only increasing or only decreasing)

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(M² log M) or O(M³) |
| **Space** | O(M²) |

**Where:**
- M = maximum sum value

---

## 🔑 Key Insights

- ✨ A bitonic sequence can be split into **increasing** and **decreasing** parts
- ✨ The **peak element** can appear once or multiple times
- ✨ Use **partition functions** to count possible subsequences
- ✨ Apply **modular arithmetic** (10⁹ + 7) to avoid overflow
- ✨ Consider **edge cases**: N = 1, monotonic sequences
- ✨ **Dynamic programming** on sum and length is essential
- ✨ The problem is related to **integer partitions** with constraints

---

## 📚 Related Topics

- Dynamic Programming
- Combinatorics
- Integer Partitions
- Sequence Analysis
- Modular Arithmetic
- Number Theory

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>