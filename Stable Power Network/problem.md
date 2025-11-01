# ⚡ Stable Power Network

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

In a futuristic telecommunication network, servers are connected by **bidirectional links** that allow the transmission of digital messages.

However, not all links are equally reliable: some sections a risk of message corruption, and all require a certain transmission time.

A message must be sent from server **1** to server **N**.

To evaluate the quality of a route, the company defines a pair of values:

- **Maximum risk** (*maxR*): the highest risk value among all links used in the route
- **Total time** (*totalT*): the sum of the transmission times of all links in the route

The company prioritizes **safety over speed**. That is, among all possible routes, it prefers the one that first **minimizes *maxR***, and in case of a tie, the one with the **smallest *totalT***.

Your task is to determine the quality of the best possible transmission from server **1** to server **N**.

If no such route exists, you must report it.

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `T` | Number of test cases |

For each test case:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `N M` | Number of servers and number of links |
| 2 to M+1 | `u v R W` | Four integers describing a bidirectional link |

**Link Description:**
- `u, v`: the servers connected by this link
- `R`: the transmission risk in milliseconds
- `W`: the corruption risk of this link

---

## 📤 Output Format

For each test case, print the answer on a separate line.

If a path exists, print two integers:
```
maxR totalT
```

representing the quality of the best route from server **1** to server **N**.

If no path exists, print `-1`.

---

## 🔒 Constraints
```
1 ≤ T ≤ 10³
2 ≤ N ≤ 2 × 10⁵
1 ≤ M ≤ 3 × 10⁵
1 ≤ u, v ≤ N for all i = 1, ..., M
1 ≤ Rᵢ ≤ 10⁹ for all i = 1, ..., M
1 ≤ Wᵢ ≤ 10⁹ for all i = 1, ..., M
0 ≤ Bᵢ ≤ 10⁹ for all i = 1, ..., M
```

### Additional Constraints

- It is guaranteed that the sum of **N** over all test cases does not exceed **2 × 10⁵**
- It is guaranteed that the sum of **M** over all test cases does not exceed **3 × 10⁵**

### ⏱️ Time and Memory Limits

- **Time limit:** 1000 ms
- **Memory limit:** 256 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This problem requires finding a path with **lexicographic optimization** (minimize max risk first, then total time):

1. **Modified Dijkstra's Algorithm**
   - Use priority queue with custom comparator
   - State: (maxRisk, totalTime, currentNode)
   - Prioritize by minimum maxRisk, then minimum totalTime

2. **Binary Search on Risk**
   - Binary search on the maximum risk value
   - For each risk threshold, find minimum time using Dijkstra
   - Find the smallest maxR that allows reaching node N

3. **Edge Relaxation**
   - When exploring edge (u, v) with risk R and time W:
   - newMaxR = max(currentMaxR, R)
   - newTotalT = currentTotalT + W
   - Update if (newMaxR, newTotalT) is lexicographically better

4. **Path Existence**
   - Use BFS/DFS first to check if path exists
   - If no path from 1 to N, output -1

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(T × (M + N) log N) or O(T × M log M × log(maxR)) |
| **Space** | O(N + M) |

**Where:**
- T = number of test cases
- N = number of servers
- M = number of links

---

## 🔑 Key Insights

- ✨ This is a **lexicographic shortest path** problem
- ✨ Prioritize **minimizing maximum risk** over total time
- ✨ Use **modified Dijkstra** with custom state comparison
- ✨ Alternative: **binary search** on maximum risk, then minimize time
- ✨ Handle **disconnected graphs** (output -1)
- ✨ The path quality is determined by the **worst link** (bottleneck problem)
- ✨ Consider using **minimax path** algorithms

---

## 📚 Related Topics

- Graph Theory
- Dijkstra's Algorithm
- Shortest Path
- Binary Search
- Minimax Path
- Lexicographic Optimization
- Priority Queue

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>