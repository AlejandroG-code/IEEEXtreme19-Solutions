# 🎯 Shailesh's Triplet

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

Shailesh has an upcoming tournament. For that he has to choose **3 integers**. So he comes up with an interesting idea. Given an integer **N**, he will select the positive integers **A, B, C** such that no two of them are equal (i.e., A ≠ B, A ≠ C, B ≠ C) which satisfy the following conditions:

- **A + B + C = 2 · N**
- **A ⊕ B ⊕ C = N** (where ⊕ represents [Bitwise XOR operator](https://en.wikipedia.org/wiki/Bitwise_operation#XOR))

As Shailesh is busy with Turing Hut club works, he asks your help in identifying the integers **A, B, C**. So, find any 3 integers that satisfy the above conditions.

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `T` | Number of test cases |
| 2 to T+1 | `N` | Single integer per test case |

**Example Structure:**
```
T
N₁
N₂
...
Nₜ
```

---

## 📤 Output Format

For each test case, output **one line**:

- ✅ If triplet exists: Three space-separated integers `A B C` that satisfy the conditions
- ❌ If no triplet exists: `-1`

> **Note:** In case of multiple triplets which satisfy the conditions, print any triplet.

---

## 🔒 Constraints
```
1 ≤ T ≤ 10⁵
1 ≤ N ∼ 2⁶³
```

### ⏱️ Time and Memory Limits

- **Time limit:** 2000 ms
- **Memory limit:** 256 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This problem requires understanding the properties of **XOR** and **addition**:

1. **Analyze XOR Properties**
   - A ⊕ B ⊕ C = N means the XOR of three numbers equals N
   - XOR eliminates bits that appear an even number of times

2. **Analyze Sum Constraint**
   - A + B + C = 2N means the sum is twice the XOR result
   - This creates a specific relationship between the numbers

3. **Check Validity**
   - Not all values of N have valid triplets
   - Need to check if a solution exists based on N's properties

4. **Construction Strategy**
   - Use bitwise properties to construct valid triplets
   - Ensure all three numbers are distinct and positive

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(T) or O(T log N) |
| **Space** | O(1) |

**Where:**
- T = number of test cases
- N = value of the input

---

## 🔑 Key Insights

- ✨ Understanding **XOR properties** is crucial for this problem
- ✨ The relationship between **sum** and **XOR** constrains possible solutions
- ✨ Not all values of N have valid triplets - detect impossibility early
- ✨ Multiple valid solutions may exist - any one is acceptable
- ✨ Consider **edge cases** where N is small or has specific bit patterns
- ✨ A simple construction: Try setting **A = N, B = N/2, C = N/2** or similar patterns

---

## 📚 Related Topics

- Bitwise Operations
- XOR Properties
- Number Theory
- Mathematical Construction
- Bit Manipulation

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>