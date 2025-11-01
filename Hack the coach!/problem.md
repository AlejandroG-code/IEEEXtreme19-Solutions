# 🔓 Hack the Coach!

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

Today your university had a very important contest, which was open for all. That's why even your coach participated on it. When you asked him about the problem **D** of the contest, he told you his solution but something seems strange.

The problem **D** goes as follows:

It is an interactive problem where you are lost in a country modeled as a tree with **N ≥ 2** vertices, rooted at vertex **R** — your hotel's location. You can query an app that, given two vertices **u** and **v**, returns their lowest common ancestor (LCA) using a function `lca(u, v)`. However, due to low battery, you can make at most **⌊N/2⌋** queries. Using these limited LCA queries, you must determine the root of the tree — the location of your hotel. After using the queries, you must print the root of the tree.

During the contest, he wanted to be fast and trusted his instincts, so he told you he sent this solution:
```python
read integer n

for i from 1 to n - 1:
    read integers u, v
    degree[u] += 1
    degree[v] += 1
    add v to adjacency list G[u]
    add u to adjacency list G[v]

initialize empty list leaves
for i from 1 to n:
    if degree[i] == 1:
        append i to leaves

initialize empty list lcas
i = 0
while i + 1 < size(leaves):
    lcas.append (leaves[i], leaves[i + 1], lca(leaves[i], leaves[i + 1]))
    i += 2

if size(leaves) is odd:
    lcas.append (leaves[0], leaves[|leaves| - 1], lca(leaves[0], leaves[|leaves| - 1]))

initialize empty list candidates
for r from 1 to n:
    if check(r, lcas):
        candidates.append(r)

assert that size(candidates) == 1
answer(candidates[0])
```

Where `check(r, lcas)` is a boolean function that validates if using node **r** as the root is valid under the restrictions of the LCA tuples **(u, v, lca(u, v))** in **lcas**.

Due to weak tests he got Accepted, but you know that this idea might fail in some case, so you want to hack his solution.

---

## 📥 Input Format

**There is no input in this problem.**

---

## 📤 Output Format

Your solution should print a single file describing a tree in which the coach's solution fails.

The first line of output must contain two integers **N ≥ 2** and **1 ≤ R ≤ N**, the number of nodes in the tree and the root of the tree, respectively.

The following **N - 1** lines must contain two integers **1 ≤ Aᵢ < Bᵢ ≤ N**, the nodes connected by the corresponding edge.

You must ensure that your output prints a **valid tree**.

The score obtained will be based on the value of **N**, the smaller, the better. To be precise, the formula for points is:

**⌊BestScore/N⌋²** where **BestScore** is the best score achieved by any team.

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

This is a **counter-example construction** problem:

1. **Analyze the Coach's Algorithm**
   - The algorithm identifies leaves (degree = 1)
   - Makes LCA queries between pairs of leaves
   - Uses LCA results to validate candidate roots
   - The bug is in the logic or query pattern

2. **Identify the Bug**
   - Line: `lcas.append (leaves[i], leaves[leaves[i] - 1], lca(leaves[0], leaves[i + 1]))`
   - The indexing `leaves[i] - 1` is likely incorrect
   - Should probably be `leaves[i + 1]` or similar

3. **Construct Counter-Example**
   - Create a tree where the buggy indexing causes failure
   - Minimize N for better score
   - Ensure the algorithm produces wrong answer or crashes

4. **Optimization Strategy**
   - Try small trees first (N = 2, 3, 4, ...)
   - Test different tree structures: star, path, balanced
   - Verify the coach's code fails on your test case

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(1) - just output construction |
| **Space** | O(N) |

**Where:**
- N = size of constructed tree

---

## 🔑 Key Insights

- ✨ This is a **code analysis** and **test case generation** problem
- ✨ The bug is in the line: `leaves[leaves[i] - 1]` - this uses a leaf's value as an index
- ✨ If `leaves[i]` has value > size of leaves array, it causes **index out of bounds**
- ✨ **Minimize N** to maximize your score
- ✨ A simple tree with carefully chosen vertex numbers will trigger the bug
- ✨ The error occurs when accessing `leaves[leaves[i] - 1]`
- ✨ Consider trees where leaf values are large (e.g., leaves = [5, 6, 7] in a small tree)

---

## 💡 Hint

Create a small tree where the **leaf node IDs** are larger than the **number of leaves**, so that `leaves[leaves[i] - 1]` causes an array index error.

---

## 📚 Related Topics

- Code Analysis
- Bug Finding
- Test Case Generation
- Tree Structures
- LCA (Lowest Common Ancestor)
- Counter-Example Construction

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>