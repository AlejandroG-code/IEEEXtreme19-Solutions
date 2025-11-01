# 🌳 Beatrice and the Dream Tree

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

Beatrice is a university student preparing for the upcoming IEEExtreme 19.0. As part of her training, she spends countless hours thinking about trees — not the ones in nature, but the rooted ones in graph theory. Her favorite tree is a rooted tree with **N** nodes, rooted at node **1**. She even memorized all of its edges and knows the label of every node: the **i-th** node has label **i** (1 ≤ i ≤ N).

One night, Beatrice has a strange dream: she wakes up inside her favorite tree. However, the labels on all nodes are gone — she no longer knows which node she is standing on. From any node, she can only observe:

- Which nodes it is directly connected to (its neighbors)
- Which of those neighbors is its parent (a special edge she can always identify)

And she can walk along edges to explore the tree.

Moreover, Beatrice has a perfect memory: once she visits a node or a path, she will never confuse it with another.

Beatrice wants to use her observations to deduce, without any doubt, the original label of as many nodes as possible. Unfortunately, due to the tree's structure, some nodes might be indistinguishable.

Your task is to help Beatrice. Determine the **maximum number of nodes** whose original labels she can uniquely identify in her dream.

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `N` | Number of nodes in the tree |
| 2 to N | `Uᵢ Vᵢ` | Two integers indicating there is an edge between nodes Uᵢ and Vᵢ |

**Example Structure:**
```
N
U₁ V₁
U₂ V₂
...
Uₙ₋₁ Vₙ₋₁
```

---

## 📤 Output Format

Print a single integer: the **maximum number of nodes** whose original labels Beatrice can uniquely identify.

---

## 🔒 Constraints
```
2 ≤ N ≤ 10⁶
1 ≤ Uᵢ, Vᵢ ≤ N for all valid i
```

### ⏱️ Time and Memory Limits

- **Time limit:** 3000 ms
- **Memory limit:** 512 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This problem requires understanding **tree isomorphism** and **automorphisms**:

1. **Tree Automorphism**
   - Find all nodes that are structurally identical (indistinguishable)
   - Two nodes are indistinguishable if swapping their labels produces an isomorphic tree
   - Use **tree hashing** or **canonical form** to identify symmetries

2. **Centroid/Center Finding**
   - Find the center(s) of the tree
   - The center is uniquely identifiable if it's a single node
   - If two centers exist, they may be indistinguishable

3. **Subtree Structure Analysis**
   - Compute hash/signature for each subtree
   - Nodes with unique subtree structures are identifiable
   - Count nodes that have no isomorphic counterparts

4. **Graph Automorphism Counting**
   - Use DFS/BFS to compute structural signatures
   - Group nodes by their structural equivalence class
   - Nodes in singleton equivalence classes are uniquely identifiable

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(N log N) or O(N) |
| **Space** | O(N) |

**Where:**
- N = number of nodes in the tree

---

## 🔑 Key Insights

- ✨ This is a **tree automorphism** problem
- ✨ Nodes are distinguishable if they have **unique structural properties**
- ✨ Use **tree hashing** to identify structurally equivalent nodes
- ✨ The tree is **rooted at node 1** - this constrains the problem
- ✨ Beatrice can identify the **root** if she knows parent-child relationships
- ✨ Nodes with **different subtree structures** are distinguishable
- ✨ Symmetric subtrees create ambiguity
- ✨ Count nodes that belong to **singleton orbit classes**

---

## 💡 Example Explanation

In the example with 8 nodes:
- The tree structure creates symmetries
- Nodes 6, 7, and 8 form a symmetric structure at the bottom
- From any of these nodes, the view is identical
- Therefore, Beatrice can uniquely identify **5 nodes** but not the 3 symmetric leaves

---

## 📚 Related Topics

- Tree Automorphism
- Graph Isomorphism
- Tree Hashing
- Structural Equivalence
- Tree Centers/Centroids
- DFS/BFS
- Canonical Forms

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>