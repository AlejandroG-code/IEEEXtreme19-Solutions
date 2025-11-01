# 🔢 Sequence Decomposition

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

An ancient ancestral saying states that the number **112012** brings good luck in any form it may appear (that is, as the number 112012, as the sequence **{1, 1, 2, 0, 1, 2}**, among others). Moreover, it is said that a sequence of characters consisting only of **0**, **1**, and **2** is considered fortunate if it can be decomposed into multiple subsequences **{1, 1, 2, 0, 1, 2}**.

Miguel has some fortunate sequences, and he will only give them to you if you can find a valid decomposition for each one. It's your time to show what you're capable of!

**Note:** A subsequence of a sequence **S** is sequence that can be derived from **S** by deleting zero or more elements without changing the order of the remaining elements. For example, sequence **{1, 2, 3, 2, 3}** contains **{1, 2, 2}** and **{1, 3, 2}** as subsequences but **{2, 3, 1}** is not contained as a subsequence.

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `T` | Number of sequences |
| 2 to T+1 | `Sᵢ` | A sequence to be decomposed |

**Example Structure:**
```
T
S₁
S₂
...
Sₜ
```

---

## 📤 Output Format

For each sequence **Sᵢ**, in the order of input, print **⌈|Sᵢ|/6⌉** lines, each containing 6 integers in increasing order, representing the indices of a subsequence **{1, 1, 2, 0, 1, 2}** such that all of them together decompose the sequence **Sᵢ**. 

If there are multiple valid answers, you may print any of them.

---

## 🔒 Constraints
```
1 ≤ T ≤ 2 × 10⁵
1 ≤ |Sᵢ| ≤ 6 × 10⁵
1 ≤ ∑ᵢ₌₁ᵀ |Sᵢ| ≤ 3 × 10⁶
Sᵢ is fortunate for all i = 1, ..., T
```

### ⏱️ Time and Memory Limits

- **Time limit:** 1000 ms
- **Memory limit:** 256 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This is a **greedy subsequence matching** problem:

1. **Understanding the Problem**
   - Must decompose string into subsequences of **{1, 1, 2, 0, 1, 2}**
   - Each character must be used exactly once
   - Output indices (1-indexed) for each subsequence
   - Guaranteed that input is "fortunate" (can be decomposed)

2. **Greedy Matching**
   - Use multiple "slots" for building subsequences
   - Each slot tracks its current position in pattern {1, 1, 2, 0, 1, 2}
   - For each character, assign it to the first available slot that needs it

3. **Pattern Tracking**
   - Pattern: [1, 1, 2, 0, 1, 2]
   - For each active subsequence, track which element we're looking for next
   - When a subsequence completes (reaches index 6), output it and reset

4. **Implementation**
   - Maintain list of active subsequences
   - Each subsequence stores: [indices collected, current_position_in_pattern]
   - Scan input left to right
   - Assign each character to first matching slot

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(∑|Sᵢ|) |
| **Space** | O(max|Sᵢ|) |

**Where:**
- |Sᵢ| = length of sequence i
- Number of active subsequences ≤ |S|/6

---

## 🔑 Key Insights

- ✨ Input is **guaranteed to be decomposable** (fortunate sequence)
- ✨ Use **greedy assignment** - assign each digit to first available slot
- ✨ Pattern is **{1, 1, 2, 0, 1, 2}** repeated
- ✨ Need to track **multiple active subsequences** simultaneously
- ✨ Output indices are **1-indexed**
- ✨ Each line contains **6 indices** (one complete subsequence)
- ✨ Use **state machine** approach for pattern matching

---

## 💡 Example Explanation

**Input:** `112012`

**Output:** `1 2 3 4 5 6`

This represents using all 6 characters (indices 1-6) to form one complete subsequence {1, 1, 2, 0, 1, 2}.

---

**Input:** `111122001122`

**Output:**
```
1 2 5 7 9 11
3 4 6 8 10 12
```

This represents two subsequences:
- Subsequence 1: indices {1, 2, 5, 7, 9, 11} → {1, 1, 2, 0, 1, 2}
- Subsequence 2: indices {3, 4, 6, 8, 10, 12} → {1, 1, 2, 0, 1, 2}

---

## 📚 Related Topics

- Greedy Algorithms
- Pattern Matching
- Subsequence Problems
- State Machine
- String Processing
- Array Manipulation

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>