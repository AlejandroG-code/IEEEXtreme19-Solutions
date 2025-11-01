# 🔢 Diameter Problem Again

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

Sergio knows everything about diameters. Therefore, Miguel — once again trying to demonstrate his teammate — decides to give him the following problem:

Given a weighted tree, whose edge weights may be negative, perform a series of operations on an initially empty list **4**.

The operations are as follows:

1. **1 x:** Append node **x** to the end of the list
2. **2:** Remove the node at the end of the list
3. **3 i r z:** Let **u** be the node in the range **[l, r]** of list **A** that is farthest from node **z**. Report the distance between nodes **r** and **z**

To prevent Sergio from using a clever algorithm, Miguel decided to encrypt the queries as follows:

- For operations of type **1** and **3**:
```
  x = (x ⊕ last_ans) (mod N) + 1
```

- Additionally, for operation **3**:
```
  l = (l ⊕ last_ans) (mod |A|) + 1
  r = (r ⊕ last_ans) (mod |A|) + 1
```
  
  If **l > r**, swap them.

Here, **last_ans** denotes the result of the previous type-3 query or 0 if there was none before.

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `N` | Number of nodes |
| 2 to N | `V W` | Three integers: edge between nodes V, W with weight W |
| N+1 | `M` | Number of operations |
| N+2 to N+M+1 | Operation | One operation per line |

**Operation Formats:**
- **Type 1:** `1 x` - one number x
- **Type 2:** `2` - no additional numbers
- **Type 3:** `3 l r x` - three numbers l, r, x

All numbers in the operations satisfy **0 < value < 2 · 10⁹**.

---

## 📤 Output Format

For each operation of type **3**, print a single integer: the distance between node **z** and the node in the specified range that is farthest from node **z**.

---

## 🔒 Constraints
```
1 ≤ N, M ≤ 3 × 10⁵
1 ≤ u, v ≤ N
|w| ≤ 500
```

### ⏱️ Time and Memory Limits

- **Time limit:** 5000 ms
- **Memory limit:** 512 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This is a **tree data structure** problem with **encrypted queries**:

1. **Tree Construction**
   - Build weighted tree from input edges
   - Edges can have negative weights

2. **Query Decryption**
   - Use XOR with last_ans to decrypt query parameters
   - Apply modulo operations to get valid indices/nodes
   - Swap l and r if necessary

3. **Distance Calculation**
   - For each type-3 query, find node in list[l:r] that is farthest from z
   - Calculate tree distances efficiently
   - Use BFS/DFS or precomputed LCA + distances

4. **Optimization**
   - Precompute all-pairs distances (if feasible)
   - Use LCA with binary lifting for distance queries
   - Distance(u, v) = dist[u] + dist[v] - 2 × dist[LCA(u,v)]

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(N² ) preprocessing + O(M × N) queries |
| **Space** | O(N²) or O(N log N) |

**Where:**
- N = number of nodes
- M = number of operations

---

## 🔑 Key Insights

- ✨ **Query encryption** using XOR with previous answer
- ✨ Tree with **negative edge weights** possible
- ✨ Need to **decrypt** parameters before processing
- ✨ Type 3 query: Find **maximum distance** from node z among nodes in list[l:r]
- ✨ Use **BFS/DFS** from node z to calculate distances
- ✨ Or use **LCA + distance arrays** for optimization
- ✨ **last_ans** starts at 0 and updates after each type-3 query
- ✨ List **A** is dynamically modified by type-1 and type-2 operations

---

## 💡 Example Walkthrough

**Initial state:**
- Tree with 5 nodes
- List A = []
- last_ans = 0

**Query 1:** `1 2`
- Decrypt: x = (2 ⊕ 0) mod 5 + 1 = 3
- Add node 3 to list: A = [3]

**Query 3:** `3 0 3`
- Decrypt: 
  - l = (0 ⊕ (-185)) mod 1 + 1 = 1
  - r = (3 ⊕ (-185)) mod 1 + 1 = 1
  - z = (... decryption ...)
- Find farthest node in A[1:1] from z
- Calculate distance and update last_ans

---

## 🔍 Algorithm Steps
```python
# Build tree
tree = build_tree(edges)

# Initialize
A = []
last_ans = 0

for operation in operations:
    if op_type == 1:
        # Decrypt and add node
        x = (x ^ last_ans) % N + 1
        A.append(x)
    
    elif op_type == 2:
        # Remove last node
        A.pop()
    
    elif op_type == 3:
        # Decrypt parameters
        l = (l ^ last_ans) % len(A) + 1
        r = (r ^ last_ans) % len(A) + 1
        z = (z ^ last_ans) % N + 1
        
        if l > r:
            l, r = r, l
        
        # Find farthest node
        max_dist = -infinity
        for i in range(l-1, r):
            node = A[i]
            dist = distance(tree, node, z)
            max_dist = max(max_dist, dist)
        
        print(max_dist)
        last_ans = max_dist
```

---

## 📚 Related Topics

- Tree Data Structures
- Graph Algorithms
- Distance Queries
- LCA (Lowest Common Ancestor)
- BFS/DFS
- Query Encryption
- XOR Operations
- Dynamic Lists

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>