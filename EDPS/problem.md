# 🧬 EDPS

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

According to an ancient tale, the answer to all of humankind's questions is a spell protected by a logical structure known as a **Well-Parenthesized Sequence (WPS)**.

A WPS is a string consisting only of the characters `(` and `)`, satisfying the following properties:

- The empty string is a WPS
- The concatenation of two WPSs is also a WPS
- A WPS enclosed in a pair of parentheses is also a WPS

A **pair of parentheses** is defined as a matching pair `(`, `)` that directly encloses a WPS.

It is known that every WPS of length **2N** contains exactly **N** such pairs.

The original spell has been lost, but researchers managed to recover one crucial piece of information: the **multiset of distances** between each matching pair of parentheses, that is, the number of symbols that appear between each `(` and its corresponding `)`.

Now the researchers need your help to **reconstruct any valid WPS** of length **2N** that has exactly **N** pairs of parentheses with the given distances. This is called an **Exactly Distanced Parentheses Sequence (EDPS)**.

If no such sequence exists, you must report it.

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `N` | Number of parenthesis pairs in the spell |
| 2 | `A₁ A₂ ... Aₙ` | N integers: the distances between the parentheses of each pair |

**Example Structure:**
```
N
A₁ A₂ ... Aₙ
```

---

## 📤 Output Format

- If there exists a WPS that satisfies all the given distances, print `Yes` on the first line, and on the second line print a string of length **2N** consisting only of the characters `(` and `)`, representing a valid sequence
- If there are multiple valid sequences, you may output any of them
- If no WPS satisfies the given conditions, print a single line with `No`

---

## 🔒 Constraints
```
1 ≤ N ≤ 20
0 ≤ Aᵢ ≤ 2N for all i = 1, ..., N
```

### ⏱️ Time and Memory Limits

- **Time limit:** 2000 ms
- **Memory limit:** 512 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This is a **constructive algorithm** and **constraint satisfaction** problem:

1. **Understanding the Problem**
   - Need to construct a valid parenthesis sequence
   - Each pair (i, j) where i is `(` and j is `)` must have distance = j - i - 1
   - Distance = number of characters between the pair
   - Must satisfy all N distances simultaneously

2. **Greedy/Backtracking Approach**
   - Sort distances (smaller distances first)
   - Try to place pairs greedily
   - Use backtracking if conflicts arise

3. **Validation**
   - Check if distances are valid (even total length)
   - Distance 0 means `()` (adjacent pair)
   - Distance d means d characters between `(` and `)`

4. **Construction Algorithm**
   - Start with empty positions
   - For each distance, try to place `(` and `)` with given distance
   - Ensure nested structure is maintained

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(N! × N) worst case with backtracking |
| **Space** | O(N) |

**Where:**
- N = number of pairs (≤ 20)

---

## 🔑 Key Insights

- ✨ **Distance definition:** For pair at positions i and j: distance = j - i - 1
- ✨ Total length must be **2N** (N opening, N closing)
- ✨ **Greedy approach:** Place smallest distances first
- ✨ Use **backtracking** for complex cases
- ✨ **Validation:** Check if all distances can be satisfied simultaneously
- ✨ Distance 0 means `()`
- ✨ **Nesting property:** Inner pairs must be completed before outer pairs can close
- ✨ N is small (≤ 20), so brute force/backtracking is feasible

---

## 💡 Example Explanations

**Example 1:**
- Input: N=1, distances=[0]
- Distance 0 means adjacent pair
- Output: `()`

**Example 2:**
- Input: N=2, distances=[0, 0]
- Two adjacent pairs
- Output: `()()` or `(())`

**Example 3:**
- Input: N=2, distances=[0, 2]
- One pair with distance 0: `()`
- One pair with distance 2: `(xx)` where xx is 2 chars
- Output: `(())` - outer pair has distance 2, inner pair has distance 0

**Example 4:**
- Input: N=1, distances=[2]
- Need distance 2, but only have 2 characters total
- Impossible → Output: `No`

**Example 5:**
- Input: N=5, distances=[0, 0, 2, 2, 6]
- Multiple valid constructions possible
- Output: `((()))()()` or similar

---

## 🔍 Algorithm Steps
```python
def construct_edps(N, distances):
    # Initialize result
    result = [''] * (2 * N)
    used = [False] * (2 * N)
    
    # Sort distances
    distances.sort()
    
    def backtrack(idx):
        if idx == N:
            return True
        
        dist = distances[idx]
        
        # Try placing pair at each valid position
        for i in range(2 * N):
            if used[i]:
                continue
            
            j = i + dist + 1
            if j >= 2 * N or used[j]:
                continue
            
            # Try placing pair
            result[i] = '('
            result[j] = ')'
            used[i] = used[j] = True
            
            if is_valid_so_far() and backtrack(idx + 1):
                return True
            
            # Backtrack
            result[i] = result[j] = ''
            used[i] = used[j] = False
        
        return False
    
    if backtrack(0):
        return 'Yes\n' + ''.join(result)
    else:
        return 'No'
```

---

## 📚 Related Topics

- Backtracking
- Constraint Satisfaction
- Parenthesis Matching
- Constructive Algorithms
- Greedy Algorithms
- String Construction
- Recursion

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>