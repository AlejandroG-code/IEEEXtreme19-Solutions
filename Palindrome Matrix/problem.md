# 🔤 Palindrome Matrix

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

It's Sunday morning, and you decided to read the newspaper to solve a crossword puzzle — but today's crossword is somewhat special.

This crossword doesn't use letters, but digits written in an **N × M** grid. Some cells are blocked, while the others are free.

A **word** in this crossword is defined as a **maximal segment** of contiguous free cells in a row or column, delimited by the grid borders or blocked cells.

Each free cell initially contains a digit. The goal is to modify these digits so that all words become **palindromes**, meaning they read the same from left to right and from right to left.

Additionally, you must **minimize the total sum of absolute differences** between the original and modified digits.

It is guaranteed that a valid solution always exists.

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `N M` | Two integers: dimensions of the crossword |
| 2 to N+1 | Grid rows | M characters per line |

**Grid Character Format:**
- `.` represents a blocked cell
- A digit `d` (0-9) represents a free cell with initial digit d

**Example Structure:**
```
N M
row₁
row₂
...
rowₙ
```

---

## 📤 Output Format

Print the completed crossword in the same format as the input, satisfying all the conditions described.

If there are multiple valid solutions, you must print the one that **minimizes the total sum of the values** in the final matrix.

---

## 🔒 Constraints
```
1 ≤ N, M ≤ 1000
```

### ⏱️ Time and Memory Limits

- **Time limit:** 2000 ms
- **Memory limit:** 512 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This problem requires **graph-based constraint satisfaction**:

1. **Identify Words**
   - Extract all maximal horizontal and vertical segments
   - Each word must be a palindrome

2. **Build Constraint Graph**
   - For each palindrome constraint, pair cells that must be equal
   - Multiple words may share cells, creating dependencies

3. **Find Connected Components**
   - Use Union-Find or DFS to group cells that must have the same value
   - All cells in a component must have identical final values

4. **Optimize Values**
   - For each component, choose the digit that minimizes total change
   - Try all digits 0-9 and calculate cost
   - Choose the digit with minimum sum of absolute differences

5. **Minimize Matrix Sum**
   - When multiple solutions have the same cost, choose smaller digits
   - This ensures the minimal total sum in the final matrix

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(N × M × 10) |
| **Space** | O(N × M) |

**Where:**
- N, M = dimensions of the grid
- 10 = number of possible digit values

---

## 🔑 Key Insights

- ✨ Use **Union-Find (Disjoint Set Union)** to group constrained cells
- ✨ Each palindrome constraint creates **equality requirements** between cells
- ✨ Choose the **median value** or try all 10 digits for each component
- ✨ Handle **overlapping words** that share cells correctly
- ✨ Minimize **sum of absolute differences** first, then minimize **total sum**
- ✨ Blocked cells (`.`) remain unchanged
- ✨ A word of length 1 is automatically a palindrome

---

## 📚 Related Topics

- Graph Theory
- Union-Find / Disjoint Set Union
- Constraint Satisfaction
- Optimization
- Palindromes
- Grid Problems
- Connected Components

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>