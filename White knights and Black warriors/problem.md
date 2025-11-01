# ⚔️ White Knights and Black Warriors

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

The IEEExtreme programming competition is in full swing, and teams from all over the world are solving tough problems. Two rival teams, the "White Knights" and the "Black Warriors", have their own nodes on a vast network of computers that form a tree structure. Each node is either controlled by the White Knights (white nodes) or the Black Warriors (black nodes).

The competition administrators, including you, want to track how close each team gets to the White Knights' nodes during their journey across the network. To do this, you've been given several tasks where you must find the **shortest distance to a white node** as teams travel between two specific nodes, **U** and **V**, in the network.

As the competition heats up, your job is to help the teams by determining how close they are to passing by a white node as they navigate between different points in the tree. This insight could be crucial for their strategies!

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `N Q` | Number of nodes (computers) and number of queries |
| 2 | `N integers` | i-th integer is 1 if node is white (White Knights), 0 if black (Black Warriors) |
| 3 to N+1 | `aᵢ bᵢ` | Two integers representing a connection between nodes aᵢ and bᵢ |
| N+2 to N+Q+1 | `Uᵢ Vᵢ` | Two integers representing a query path between Uᵢ and Vᵢ |

**Example Structure:**
```
N Q
color₁ color₂ ... colorₙ
a₁ b₁
a₂ b₂
...
aₙ₋₁ bₙ₋₁
U₁ V₁
U₂ V₂
...
Uᵩ Vᵩ
```

---

## 📤 Output Format

For each query, output the **minimum distance to a white node** on the path between **Uᵢ** and **Vᵢ**. It's guaranteed that at least a white node exists.

---

## 🔒 Constraints
```
1 ≤ N ≤ 10⁵
1 ≤ Q ≤ 10⁵
1 ≤ aᵢ, vᵢ ≤ N for all valid i
1 ≤ Uᵢ, Vᵢ ≤ N for all valid i
```

### ⏱️ Time and Memory Limits

- **Time limit:** 1000 ms
- **Memory limit:** 256 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This is a **tree path query** problem:

1. **Tree Structure**
   - Build tree from edges
   - Each node is either white (1) or black (0)
   - Tree structure (N-1 edges for N nodes)

2. **Path Finding**
   - For each query (U, V), find the path between U and V
   - Use LCA (Lowest Common Ancestor) or DFS/BFS

3. **Minimum Distance to White Node**
   - For each node on the path from U to V:
     - Find the closest white node from that node
     - Track the minimum distance across all nodes on path

4. **Optimization Strategies**
   - **Precompute distances:** Use BFS from each white node
   - **LCA with binary lifting:** Find path efficiently
   - **Path decomposition:** Extract nodes on path U→V
   - For each node on path, find minimum distance to any white node

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O((N + Q) × N) or O(N log N + Q × log N) with optimization |
| **Space** | O(N²) or O(N log N) |

**Where:**
- N = number of nodes
- Q = number of queries

---

## 🔑 Key Insights

- ✨ The network forms a **tree structure** (connected, acyclic)
- ✨ Need to find **path between U and V** in tree
- ✨ For each node on path, find **distance to nearest white node**
- ✨ Use **multi-source BFS** from all white nodes to precompute distances
- ✨ Or use **LCA** to find path, then check distances
- ✨ **At least one white node** is guaranteed to exist
- ✨ Answer is the **minimum** distance among all nodes on the path

---

## 💡 Solution Approach

### Method 1: Multi-Source BFS
```python
# Precompute distances from all white nodes
def multi_source_bfs(tree, white_nodes):
    dist = [infinity] * (N + 1)
    queue = deque()
    
    # Start BFS from all white nodes
    for node in white_nodes:
        dist[node] = 0
        queue.append(node)
    
    while queue:
        u = queue.popleft()
        for v in tree[u]:
            if dist[v] > dist[u] + 1:
                dist[v] = dist[u] + 1
                queue.append(v)
    
    return dist

# For each query
def answer_query(U, V, tree, dist_to_white):
    path = find_path(tree, U, V)
    min_dist = min(dist_to_white[node] for node in path)
    return min_dist
```

### Method 2: Path + Individual BFS
```python
# Find path using DFS/BFS or LCA
path = find_path_in_tree(U, V)

# For each node on path, find closest white node
min_distance = infinity
for node in path:
    if is_white[node]:
        min_distance = 0
        break
    else:
        # BFS to find closest white node
        dist = bfs_to_white(node, tree, is_white)
        min_distance = min(min_distance, dist)

print(min_distance)
```

---

## 📊 Example Explanation

**Given graph:**
- Node colors: [1, 0, 0, 0, 0, 0]
- Node 1 is white, others are black

**Query:** U=5, V=8
- Path: 5 → 2 → 3 → 8
- Distances to white nodes:
  - Node 5: distance 2 (to node 1)
  - Node 2: distance 1 (to node 1)
  - Node 3: distance 2 (to node 1)
  - Node 8: distance 3 (to node 1)
- **Minimum:** 0 (since we pass through or near white node)

**Output:** 0

---

## 📚 Related Topics

- Tree Data Structures
- Graph Traversal (BFS/DFS)
- Lowest Common Ancestor (LCA)
- Path Queries
- Multi-Source BFS
- Distance Computation
- Tree Paths

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>