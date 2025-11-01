# 🔄 Become as One

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

Given an array **A** of **N** integers, you will have to answer **Q** queries **(Li, Ri)**. For each query, you must answer whether the subarray **A[Li, Ri]** holds the following property:

- An operation is defined as taking two occurrences of a value **X**, removing those occurrences and adding **X + 1** to the elements. Determine if **A[Li, Ri]** can finish with only **1 element** after a certain number of operations.

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `N Q` | N = length of array, Q = number of queries |
| 2 | `A1 A2 ... AN` | Array elements |
| 3 to Q+2 | `Li Ri` | Query bounds for i-th query |

**Example Structure:**
```
N Q
A1 A2 A3 ... AN
L1 R1
L2 R2
...
LQ RQ
```

---

## 📤 Output Format

For each query, print **"Yes"** if the corresponding subarray holds the property or **"No"** otherwise.

---

## 🔒 Constraints
```
1 ≤ N, Q ≤ 10⁶
0 ≤ Ai ≤ 30 for all i = 1, ..., N
1 ≤ Li ≤ Ri ≤ N for all i = 1, ..., Q
```

### ⏱️ Time and Memory Limits

- **Time limit:** 1000 ms
- **Memory limit:** 256 MB

---

## 📊 Sample Input/Output

**Input:**
```
7 4
6 5 1 3 4 1 4
1 6
2 6
4 6
1 2
```

**Output:**
```
Yes
Yes
No
No
```

---

## 🎓 Solution Approach

### Algorithm Strategy

This problem involves **greedy simulation** and **counting frequencies**:

1. **Understanding the Operation**
   - Take two identical values X and replace them with one X+1
   - Goal: reduce subarray to exactly one element
   - Operation is similar to binary merging upward

2. **Key Insight**
   - For a subarray to reduce to one element, the total "weight" must be a power of 2
   - Each element contributes 2^(value) to the total weight
   - The sum of 2^(Ai) for all elements in range must be a power of 2

3. **Mathematical Approach**
   - Calculate sum = Σ(2^Ai) for i in [L, R]
   - Check if sum is a power of 2
   - Use bit manipulation: sum & (sum-1) == 0

4. **Optimization**
   - Precompute prefix sums of 2^Ai values
   - Answer queries in O(1) after O(N) preprocessing
   - Handle potential overflow with careful arithmetic

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(N + Q) |
| **Space** | O(N) |

**Where:**
- N = array length
- Q = number of queries

---

## 🔑 Key Insights

- ✨ The problem is equivalent to checking if **Σ(2^Ai) is a power of 2**
- ✨ Use **prefix sums** to answer range queries efficiently
- ✨ **Bit manipulation** can quickly check if a number is a power of 2
- ✨ Since Ai ≤ 30, 2^Ai fits in standard integer types
- ✨ The operation simulates **binary tree merging** from leaves to root
- ✨ Two identical values can always combine to form the next level
- ✨ Success requires perfect **binary balance** in the value distribution

---

## 🧮 Mathematical Foundation

The operation can be viewed as:
- Each element Ai contributes **2^Ai** "units"
- Combining two X values creates one (X+1) value
- This represents: 2^X + 2^X = 2^(X+1)
- Final state has one element iff total units = 2^k for some k

**Example:**
- Array [1, 1, 2]: contributes 2¹ + 2¹ + 2² = 2 + 2 + 4 = 8 = 2³ ✓
- Array [1, 3]: contributes 2¹ + 2³ = 2 + 8 = 10 ≠ 2^k ✗

---

## 📚 Related Topics

- Greedy Algorithms
- Bit Manipulation
- Prefix Sums
- Range Queries
- Powers of Two
- Binary Trees
- Combinatorial Game Theory

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>
