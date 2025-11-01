# ✈️ Airline Traveling

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

Sebastian has been saving a lot of miles on his card for traveling. However, his favorite airline, 'Star Airlines', is going out of business and taking their miles with them! Sebastian wants to use his miles while he can, so he decides to take one last trip, and he wants to use all his miles, even if he has to go through any one city more than once.

'Star Airlines' is a pretty weird airline. They are a local airline that operates only in Star Country and has **N** cities, with the capital being city **0**. 'Star Airlines' has flights from the capital city to every other city and from every city to the capital, but not between cities.

Sebastian knows the cost in miles of flying from the capital to any city, and he knows it's the same price the other way around. To plan his last trip, he needs to see his options, so he will ask you if it is possible to travel from city **A** to city **B** while using all his miles. Help him by answering his questions!

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `N k` | Two integers: number of cities and number of miles Sebastian has |
| 2 | `C₁ ... Cₙ₋₁` | N-1 integers, where Cᵢ is the cost in miles to go from the capital to city i |
| 3 | `Q` | Number of queries you'll have to answer |
| 4 to Q+3 | `Aⱼ Bⱼ` | Two integers: the queries Sebastian will ask you |

**Example Structure:**
```
N k
C₁ C₂ ... Cₙ₋₁
Q
A₁ B₁
A₂ B₂
...
Aᵩ Bᵩ
```

---

## 📤 Output Format

Print **Q** lines. Print `Yes` if it is possible to go from city **Aⱼ** to **Bⱼ**, or `No` otherwise.

---

## 🔒 Constraints
```
1 ≤ N, Q ≤ 10⁶
1 ≤ k ≤ 10000
1 ≤ Cᵢ ≤ 1000 for all i = 1, ..., N - 1
0 ≤ Aⱼ, Bⱼ < N for all j = 1, ..., Q
```

### ⏱️ Time and Memory Limits

- **Time limit:** 1500 ms
- **Memory limit:** 256 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This is a **graph theory** problem with **path existence** constraints:

1. **Understanding the Graph Structure**
   - City 0 is the capital (hub)
   - All flights go through the capital (star topology)
   - Cost from city i to capital = cost from capital to city i = Cᵢ

2. **Path Calculation**
   - To go from city A to city B (where A ≠ 0 and B ≠ 0):
     - Must go through capital: A → 0 → B
     - Total cost = Cₐ + Cᵦ
   - If A = 0: Direct flight to B, cost = Cᵦ
   - If B = 0: Direct flight from A, cost = Cₐ
   - If A = B: No miles needed (already there), cost = 0

3. **Using All Miles**
   - Sebastian wants to use **exactly k miles**
   - Can visit cities multiple times
   - Need to check if we can make a path that uses exactly k miles

4. **Key Insight**
   - If we need to use exactly k miles from A to B:
     - Minimum cost = direct path cost
     - Can add extra round trips to/from capital
     - Each round trip from any city costs 2×Cᵢ
   - Check if (k - direct_cost) can be made using round trips

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(N + Q) |
| **Space** | O(N) |

**Where:**
- N = number of cities
- Q = number of queries

---

## 🔑 Key Insights

- ✨ The graph is a **star topology** centered at capital (city 0)
- ✨ All paths between non-capital cities go **through the capital**
- ✨ Must use **exactly k miles** (not less, not more)
- ✨ Can revisit cities to consume extra miles
- ✨ Calculate **minimum cost** from A to B, then check if remaining miles can be used
- ✨ Remaining miles must be **even** and achievable with round trips
- ✨ **Special cases:** A = B (cost 0), A = 0 or B = 0 (direct flight)

---

## 💡 Solution Logic

For a query from A to B:

1. Calculate minimum direct cost:
   - If A = B: cost = 0
   - If A = 0: cost = Cᵦ
   - If B = 0: cost = Cₐ
   - Otherwise: cost = Cₐ + Cᵦ

2. Calculate remaining miles: `remaining = k - direct_cost`

3. Check if remaining can be used:
   - Must be non-negative
   - Must be even (all round trips cost 2×Cᵢ)
   - Must be achievable with available round trips

4. Find minimum round trip cost (GCD consideration)

---

## 📚 Related Topics

- Graph Theory
- Star Topology
- Path Finding
- Number Theory
- Parity Checking
- GCD/LCM
- Modular Arithmetic

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>