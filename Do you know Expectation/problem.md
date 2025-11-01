# 🎲 Do you know Expectation?

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

Miguel thinks he knows a lot about probabilities, so he decided to challenge himself with the following problem to stay humble:

You are given a sequence **A₁, A₂, ..., Aₙ**.

A subsequence **S** is chosen randomly, each element is independently picked with probability **½**.

Let **X** be the XOR of all elements in **S**.

Compute the expected value of **X^K** for a fixed **K**, i.e. **E[X^K]**.

**Note:** The XOR of an empty set is 0.

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `N K` | Two integers: size of sequence and power K |
| 2 | `A₁ A₂ ... Aₙ` | N integers: the i-th element of the sequence |

**Example Structure:**
```
N K
A₁ A₂ A₃ ... Aₙ
```

---

## 📤 Output Format

Print a single line with the answer rounded up to two decimals.

---

## 🔒 Constraints
```
1 ≤ N ≤ 5 × 10⁵
1 ≤ K ≤ 6
0 ≤ Aᵢ < 1024
```

### ⏱️ Time and Memory Limits

- **Time limit:** 1000 ms
- **Memory limit:** 256 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This is a **probability** and **XOR properties** problem:

1. **Understanding the Problem**
   - Each element has ½ probability of being in subsequence S
   - Need to compute E[X^K] where X = XOR of all elements in S
   - There are 2^N possible subsequences (including empty)

2. **Key Insight: Linearity of Expectation**
   - E[X^K] = Σ (value^K × probability) for all possible XOR values
   - Each subsequence has probability (½)^N

3. **Enumerate All Subsequences**
   - Use bit manipulation to enumerate all 2^N subsequences
   - For each subsequence, compute XOR of selected elements
   - Compute value^K and accumulate

4. **Optimization for Small N**
   - Since N ≤ 5×10⁵ but Aᵢ < 1024, XOR values are limited
   - Can use frequency counting: count how many subsequences give each XOR value
   - Then compute: E[X^K] = Σ (xor_value^K × count) / 2^N

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(2^N) or O(N × 1024) with optimization |
| **Space** | O(2^N) or O(1024) |

**Where:**
- N = size of sequence
- K = power value (≤ 6)

---

## 🔑 Key Insights

- ✨ Use **linearity of expectation**: E[X^K] = Σ P(X=v) × v^K
- ✨ Each subsequence has equal probability: **1/2^N**
- ✨ XOR values are bounded: **0 ≤ XOR < 1024**
- ✨ Can use **frequency array** instead of enumerating all subsequences
- ✨ **Dynamic Programming** approach:
  - dp[i][xor] = number of subsequences using first i elements with XOR = xor
  - Transition: dp[i+1][xor] += dp[i][xor] (don't take element)
  - dp[i+1][xor ⊕ Aᵢ] += dp[i][xor] (take element)
- ✨ For large N, use **DP with XOR values** instead of full enumeration

---

## 💡 Example Explanation

**Input:**
```
4 2
0 1 2 3
```

**Possible subsets and their contributions:**

| Subset | XOR | XOR² | Probability |
|--------|-----|------|-------------|
| ∅ | 0 | 0 | 1/16 |
| {0} | 0 | 0 | 1/16 |
| {1} | 1 | 1 | 1/16 |
| {0,1} | 1 | 1 | 1/16 |
| {2} | 2 | 4 | 1/16 |
| {0,2} | 2 | 4 | 1/16 |
| {1,2} | 3 | 9 | 1/16 |
| {0,1,2} | 3 | 9 | 1/16 |
| ... | ... | ... | ... |

**Expected value:**
E[X²] = (1/16) × (0 + 0 + 1 + 1 + 4 + 4 + 9 + 9 + ...) = **3.50**

---

## 🔍 DP Algorithm
```python
# Initialize DP
dp = [0] * 1024
dp[0] = 1  # Empty subsequence

# Process each element
for a in A:
    new_dp = dp.copy()
    for xor in range(1024):
        if dp[xor] > 0:
            new_dp[xor ^ a] += dp[xor]
    dp = new_dp

# Calculate expectation
total = sum(dp)
expectation = sum(xor**K * count for xor, count in enumerate(dp)) / total
```

---

## 📚 Related Topics

- Probability Theory
- Expected Value
- XOR Properties
- Dynamic Programming
- Bit Manipulation
- Linearity of Expectation
- Combinatorics

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>