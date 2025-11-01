# 🔄 Circular Permutation

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

**Josh** is organizing a party and has invited **N** of his friends. The friends are numbered in **increasing order of their heights**; either **clockwise or anti-clockwise**.

Unfortunately, when the friends arrived, they do not all sit in one of them has **decided to move to other seats**, in order to satisfy the setup of the party. Each friend will **move around the table** from their initial seat to the designated seat either **clockwise or anti-clockwise**, whichever route is **shorter**. Josh would like to **minimize the longest distance traveled** by any of his friends.

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `N` | Single integer N |
| 2 | `permutation` | Permutation of size N, representing the initial seating of Josh's friends |

**Example Structure:**
```
N
P1 P2 P3 ... PN
```

---

## 📤 Output Format

Print a single integer, representing the **minimum longest distance traveled** by any of Josh's friends, in order to get a correct seating configuration.

---

## 🔒 Constraints
```
3 ≤ N ≤ 10⁵
```

### ⏱️ Time and Memory Limits

- **Time limit:** 1000 ms
- **Memory limit:** 256 MB

---

## 📊 Sample Input/Output

**Input 1:**
```
5
1 2 1 3 4
```
**Output 1:**
```
0
```
**Explanation:**
The guests are already seated in a valid order.

---

**Input 2:**
```
7
4 2 7 3 5 6 1
```
**Output 2:**
```
1
```
**Explanation:**
The final configuration will be:
```
3 2 1 7 6 5 4
```

---

**Input 3:**
```
10
10 1 9 2 8 3 7 4 5 6
```
**Output 3:**
```
1
```

---

## 🎓 Solution Approach

### Algorithm Strategy

This problem involves **circular arrangement optimization** and **binary search**:

1. **Understanding the Problem**
   - Friends need to be arranged in increasing/decreasing order around circular table
   - Each person moves via shortest path (clockwise or counter-clockwise)
   - Goal: minimize the maximum distance any person travels

2. **Key Observations**
   - Valid arrangements: increasing clockwise OR decreasing clockwise
   - For circular table: distance between positions i and j is min(|i-j|, N-|i-j|)
   - We need to try both orientations and all possible starting positions

3. **Binary Search Approach**
   - Binary search on the answer (maximum distance)
   - For each candidate distance D, check if arrangement is possible
   - Check all rotations of both increasing and decreasing sequences

4. **Validation Function**
   - For a given max distance D and target arrangement:
   - Check if each person can reach their target position within distance D
   - Use greedy assignment or Hungarian algorithm for optimal matching

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(N² log N) |
| **Space** | O(N) |

**Where:**
- N = number of friends

---

## 🔑 Key Insights

- ✨ **Two valid arrangements**: increasing or decreasing order clockwise
- ✨ **Circular distance**: min(clockwise, counter-clockwise) between any two positions
- ✨ **Binary search** on the maximum distance for optimization
- ✨ **All rotations** of valid sequences must be considered
- ✨ **Greedy matching** can determine if arrangement is feasible for given max distance
- ✨ **Symmetry**: decreasing clockwise = increasing counter-clockwise
- ✨ The problem is equivalent to finding **minimum bottleneck assignment**

---

## 💡 Algorithm Implementation Strategy

### Method 1: Binary Search + Validation
```pseudocode
function minMaxDistance(permutation):
    left = 0, right = N/2
    
    while left < right:
        mid = (left + right) / 2
        if canArrange(permutation, mid):
            right = mid
        else:
            left = mid + 1
    
    return left

function canArrange(permutation, maxDist):
    // Try increasing order
    for rotation in 0 to N-1:
        if validAssignment(permutation, increasingRotation[rotation], maxDist):
            return true
    
    // Try decreasing order  
    for rotation in 0 to N-1:
        if validAssignment(permutation, decreasingRotation[rotation], maxDist):
            return true
    
    return false

function validAssignment(current, target, maxDist):
    // Check if bipartite matching exists with distance constraint
    return bipartiteMatching(current, target, maxDist)
```

### Method 2: Direct Enumeration
```pseudocode
function minMaxDistance(permutation):
    minAnswer = N/2
    
    // Try all valid target arrangements
    for each valid circular arrangement:
        maxDist = computeMaxDistance(permutation, arrangement)
        minAnswer = min(minAnswer, maxDist)
    
    return minAnswer
```

---

## 🧮 Distance Calculation

For circular table with N positions:
- **Linear distance** between positions i and j: |i - j|
- **Circular distance**: min(|i - j|, N - |i - j|)
- **Maximum possible distance**: ⌊N/2⌋

**Example** (N=7):
- Distance from position 0 to position 3: min(3, 7-3) = min(3, 4) = 3
- Distance from position 0 to position 6: min(6, 7-6) = min(6, 1) = 1

---

## 📚 Related Topics

- Binary Search
- Circular Arrays
- Bipartite Matching
- Hungarian Algorithm
- Permutation Cycles
- Optimization Problems
- Greedy Algorithms
- Graph Theory

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>
