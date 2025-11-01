# 🧬 Squared Gaps

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

You are given two DNA sequences consisting of the uppercase english characters **A**, **G**, **T** and **C**. In the classical sequence alignment problem, the alignment cost is calculated based on three factors: **match** (when the same characters from both sequences are aligned), **mismatch** (when different characters are aligned), and **gap** (when a character is aligned with a space).

In this variation of the problem, the **gap cost is modified**. Specifically, when multiple consecutive spaces are aligned together in one sequence, the cost for this segment of **m** spaces is calculated as **m² · (gap cost)** rather than just **m · (gap cost)**. These space segments must be maximal, meaning there must not be any additional spaces to the left or right of the segments in the corresponding sequence after the alignment.

Given two sequences and the costs for a match, a mismatch, and a gap, your task is to determine the **maximum possible alignment cost** between these two sequences using the modified gap cost rule.

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `n` | Length of the first sequence |
| 2 | `a` | String of length n, the first sequence |
| 3 | `m` | Length of the second sequence |
| 4 | `b` | String of length m, the second sequence |
| 5 | `match mismatch gap` | Three integers: cost of match, mismatch, and gap |

**Example Structure:**
```
n
a
m
b
match mismatch gap
```

---

## 📤 Output Format

Print a single line: the **optimal alignment cost** of the two given sequences.

---

## 🔒 Constraints
```
1 ≤ n, m ≤ 10⁶
-10⁵ ≤ gap ≤ mismatch ≤ 0 ≤ match ≤ 10⁵
It is guaranteed that n · m doesn't exceed 10⁶
```

### ⏱️ Time and Memory Limits

- **Time limit:** 3000 ms
- **Memory limit:** 512 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This is a **modified sequence alignment** problem using **dynamic programming**:

1. **Understanding the Modified Gap Cost**
   - Traditional gap cost: linear (m gaps = m × gap_cost)
   - Modified gap cost: quadratic for consecutive gaps (m gaps = m² × gap_cost)
   - Consecutive gaps must be **maximal** (cannot extend further)

2. **Dynamic Programming State**
   - `dp[i][j]` = optimal alignment cost for first i characters of sequence a and first j characters of sequence b
   - Need to track gap segments separately

3. **State Transitions**
   - **Match/Mismatch:** `dp[i][j] = dp[i-1][j-1] + (match if a[i]==b[j] else mismatch)`
   - **Gap in sequence b:** Open a gap segment of length k, cost = k² × gap
   - **Gap in sequence a:** Open a gap segment of length k, cost = k² × gap

4. **Optimization**
   - For each position, try all possible gap lengths
   - Use the quadratic gap cost formula: k² × gap_cost
   - Consider both maximizing and minimizing depending on gap sign

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(n × m × max(n, m)) worst case, can be optimized |
| **Space** | O(n × m) |

**Where:**
- n = length of first sequence
- m = length of second sequence

---

## 🔑 Key Insights

- ✨ **Quadratic gap penalty** changes the optimal alignment strategy
- ✨ Consecutive gaps are **more expensive** than in linear gap models (if gap < 0)
- ✨ Or **less expensive** per gap if gap > 0 (reward for longer gaps)
- ✨ Need to consider **all possible gap lengths** at each position
- ✨ Use **DP with gap segment tracking**
- ✨ The constraint **n · m ≤ 10⁶** is crucial for complexity
- ✨ Maximal gap segments mean no gaps immediately before or after
- ✨ Similar to **affine gap penalty** but with quadratic cost

---

## 💡 Example Explanation

**Input:**
```
7
GATAGC
8
CGCCTAAC
15 -3 -20
```

**Optimal Alignment:**
```
1  - G A T A G C
2  C G G C T A A C
3
```

**Cost Calculation:**
- 1 gap segment of length 1: 1² × (-20) = -20
- 3 matches: 3 × 15 = 45
- 4 mismatches: 4 × (-3) = -12

**Total:** -20 + 45 - 12 = **13**

---

## 📚 Related Topics

- Dynamic Programming
- Sequence Alignment
- Bioinformatics
- String Algorithms
- Gap Penalty Models
- Needleman-Wunsch Algorithm
- Edit Distance

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>