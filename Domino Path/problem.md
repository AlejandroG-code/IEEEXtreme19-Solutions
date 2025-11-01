# 🎲 Domino Path

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

Almost everyone is familiar with dominoes — tiles of size **1 × 2** with two values, one on each half. In this problem, we represent each domino as a pair **(x, y)** where **1 ≤ x < y ≤ 7**.

Two dominoes can be **connected** if they share a common number. They are joined through that number, leaving the other two ends free.

For example, consider dominoes **(1, 3)** and **(2, 3)**. They can be connected through the number **3**, resulting in a sequence with free ends **1** and **2**. Then, you could connect domino **(2, 5)** to the end with **2**, and so on.

You are given a set of dominoes and must determine how many of its **non-empty** subsets hold the following condition:

- It is possible to arrange all of the dominoes in the subset to form a **single continuous chain**, where each adjacent pair of dominoes shares a common value.

However, your task does not end there — you will need to answer this question for multiple test cases.

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `T` | Number of test cases |

For each test case:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `M` | Number of dominoes in the set |
| 2 to M+1 | `xᵢ yᵢ` | Two integers: values of each half of the domino |

**Example Structure:**
```
T
M₁
x₁ y₁
x₂ y₂
...
xₘ yₘ
M₂
...
```

---

## 📤 Output Format

For each test case, print a single line: the **number of subsets** of the corresponding set that can form a single continuous chain.

---

## 🔒 Constraints
```
1 ≤ T ≤ 5 × 10⁵
1 ≤ xᵢ < yᵢ ≤ 7, for all valid i
The sum of all M across the test cases doesn't exceed 5 × 10⁵
```

### ⏱️ Time and Memory Limits

- **Time limit:** 1500 ms
- **Memory limit:** 256 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This is a **graph theory** and **combinatorics** problem:

1. **Understanding Domino Chains**
   - Dominoes form a graph where each value (1-7) is a node
   - Each domino (x, y) is an edge between nodes x and y
   - A valid chain = Eulerian path in the graph

2. **Eulerian Path Conditions**
   - A graph has an Eulerian path if:
     - All vertices with non-zero degree are connected (one component)
     - Exactly 0 or 2 vertices have odd degree

3. **Subset Enumeration**
   - For each non-empty subset of dominoes (2^M - 1 subsets)
   - Build a graph from that subset
   - Check if it forms a valid chain (Eulerian path exists)

4. **Optimization**
   - Use bit manipulation to enumerate subsets
   - For each subset, use Union-Find to check connectivity
   - Count odd-degree vertices efficiently

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(T × 2^M × M) worst case |
| **Space** | O(M) |

**Where:**
- T = number of test cases
- M = number of dominoes per test case

---

## 🔑 Key Insights

- ✨ This is an **Eulerian path** problem in disguise
- ✨ Each domino represents an **edge** in a graph (nodes are values 1-7)
- ✨ A valid chain exists iff the graph has an **Eulerian path**
- ✨ Eulerian path conditions:
  - Graph is **connected** (all non-isolated vertices)
  - **0 or 2** vertices have odd degree
- ✨ Use **bit manipulation** to enumerate all 2^M subsets
- ✨ Use **Union-Find** or **DFS** to check connectivity
- ✨ Count vertices with **odd degree**

---

## 💡 Example Explanation

**Input:**
```
3
4
1 2
2 3
3 4
1 2
```

**Valid chains include:**
- Single domino: (1,2), (2,3), (3,4) → 3 subsets
- Two dominoes: (1,2)-(2,3), (2,3)-(3,4) → 2 subsets
- Three dominoes: (1,2)-(2,3)-(3,4) → 1 subset
- And others...

**Total:** 13 valid subsets

---

## 🔍 Algorithm Steps
```
For each test case:
  For each non-empty subset (bitmask):
    1. Build graph from subset dominoes
    2. Check if all vertices are connected (Union-Find)
    3. Count vertices with odd degree
    4. If connected AND (odd_count == 0 OR odd_count == 2):
         increment valid_count
  Output valid_count
```

---

## 📚 Related Topics

- Graph Theory
- Eulerian Path
- Union-Find (Disjoint Set Union)
- Bit Manipulation
- Subset Enumeration
- Connectivity
- Combinatorics

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>