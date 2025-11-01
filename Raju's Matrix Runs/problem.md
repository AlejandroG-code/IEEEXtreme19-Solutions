# 🏃‍♂️ Raju's Matrix Runs

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

Our character **Raju** finds himself caught up in a matrix of order **N × M**, where each cell contains positive integer values. He is only allowed to move **horizontally and vertically** (left, right, up, and down), and no moves are allowed **diagonally or outside** of the matrix boundaries. Raju needs to follow a sequence of cells with **increasing values** and has the **maximum length possible**.

The uppermost row has index **0** and the lowermost row has index **N - 1**, while the leftmost column has index **0** and the rightmost column has index **M - 1**. For example, consider the given matrix of order **4 × 4** in the given matrix, the maximum increasing sequence of values is formed by the cells **(3, 1) → (3, 0) → (2, 0) → (1, 0) → (0, 0) → (0, 1)**, so it has a length of **6**.

**Example Matrix:**
```
8  9  6  5
1  2  0  1
1  5  0  2
2  1  8  4
```

Can you help Raju solving this problem?

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `N M` | N = number of rows, M = number of columns |
| 2 to N+1 | `Ai,j` | Matrix elements (i-th row contains M integers) |

**Example Structure:**
```
N M
A1,1 A1,2 ... A1,M
A2,1 A2,2 ... A2,M
...
AN,1 AN,2 ... AN,M
```

---

## 📤 Output Format

The output should contain a single integer representing the **maximum value** of the sequence (number of cells) Raju can follow in the matrix.

---

## 🔒 Constraints
```
1 ≤ N, M ≤ 200
1 ≤ Ai,j ≤ 2³¹ - 1
```

### ⏱️ Time and Memory Limits

- **Time limit:** 1000 ms
- **Memory limit:** 256 MB

---

## 📊 Sample Input/Output

**Input:**
```
4 4
8 9 6 5
1 2 0 1
1 5 0 2
2 1 8 4
```

**Output:**
```
6
```

**Explanation:**
The test's answer was explained in the statement.

---

## 🎓 Solution Approach

### Algorithm Strategy

This problem requires **Dynamic Programming** with **DFS/BFS** or **Topological Sorting**:

1. **Understanding the Problem**
   - Find the longest increasing path in a matrix
   - Movement allowed: up, down, left, right (4-directional)
   - Path must have strictly increasing values
   - Goal: maximize path length

2. **Dynamic Programming Approach**
   - Use memoization with DFS from each cell
   - `dp[i][j]` = longest increasing path starting from cell (i,j)
   - For each cell, explore all 4 directions and take maximum
   - Recurrence: `dp[i][j] = 1 + max(dp[ni][nj])` where `matrix[ni][nj] > matrix[i][j]`

3. **Topological Sorting Approach**
   - Treat matrix as a directed graph
   - Edge from (i,j) to (ni,nj) if `matrix[ni][nj] > matrix[i][j]` and adjacent
   - Apply topological sort with longest path algorithm
   - More efficient for dense graphs

4. **Implementation Steps**
   - Try starting from every cell in the matrix
   - Use memoization to avoid recalculating subproblems
   - Return the maximum path length found

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(N × M) |
| **Space** | O(N × M) |

**Where:**
- N = number of rows
- M = number of columns

**Note:** Each cell is visited at most once due to memoization.

---

## 🔑 Key Insights

- ✨ This is a **Longest Increasing Path** problem in a 2D matrix
- ✨ **Memoization** is crucial to avoid exponential time complexity
- ✨ Each cell can be the **starting point** of a potential longest path
- ✨ **4-directional movement** means each cell has at most 4 neighbors
- ✨ **Strictly increasing** constraint ensures no cycles in the path graph
- ✨ The problem is equivalent to finding the **longest path in a DAG**
- ✨ **Topological sorting** can provide an alternative elegant solution
- ✨ **Bottom-up DP** can also work by processing cells in sorted order

---

## 💡 Algorithm Implementation Strategy

### Method 1: DFS with Memoization
```pseudocode
function longestIncreasingPath(matrix):
    memo = empty 2D array
    maxLength = 0
    
    for each cell (i, j) in matrix:
        maxLength = max(maxLength, dfs(i, j, matrix, memo))
    
    return maxLength

function dfs(i, j, matrix, memo):
    if memo[i][j] != 0:
        return memo[i][j]
    
    length = 1
    for each direction (up, down, left, right):
        ni, nj = next position in direction
        if isValid(ni, nj) and matrix[ni][nj] > matrix[i][j]:
            length = max(length, 1 + dfs(ni, nj, matrix, memo))
    
    memo[i][j] = length
    return length
```

### Method 2: Topological Sort
```pseudocode
function longestIncreasingPath(matrix):
    build directed graph from matrix
    apply topological sort
    return longest path in sorted order
```

---

## 📚 Related Topics

- Dynamic Programming
- Depth-First Search (DFS)
- Memoization
- Topological Sorting
- Longest Path in DAG
- Graph Algorithms
- Matrix Traversal
- 2D Grid Problems

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>
