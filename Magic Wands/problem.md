# 🪄 Magic Wands

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

In the idyllic kingdom of Happy Land, there are **N** inhabitants, each uniquely identified by a number from **1 to N**. On any given day, each inhabitant can be in a state of **Happiness (H)** or **Sadness (S)**.

The Queen, eager to ensure the well-being of her people, desires that every single inhabitant in the kingdom be happy. To achieve this, she possesses a magic wand with a peculiar power: when used, she can change the mood of exactly **K** consecutive people according to their id, flipping their current state (if they were happy, they become sad; if they were sad, they become happy).

Could you help the queen fulfill her wish?

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `T` | Number of test cases |

For each test case:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `N K S` | N = number of inhabitants, K = parameter, S = initial state string |

**String Format:**
- The following **T** lines contain two integers **N** and **K**, and a string **S** of length **N** consisting of characters `H` and `S`
- The **i-th** character of **S** represents the initial state of the inhabitant with ID **i**: `H` for happy, `S` for sad

---

## 📤 Output Format

For each test case, print a single integer — the **minimum number of times** the Queen must use her magic wand to make all inhabitants happy.

If it is impossible to achieve this, print `-1`.

---

## 🔒 Constraints
```
1 ≤ T ≤ 10⁵
1 ≤ N, K ≤ 10⁵
S[i] is either H or S
The sum of N across all the test cases doesn't exceed 2 × 10⁵
```

### ⏱️ Time and Memory Limits

- **Time limit:** 2500 ms
- **Memory limit:** 256 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This is a **greedy flip/toggle problem**:

1. **Greedy Approach**
   - Scan from left to right (position 1 to N)
   - Whenever we encounter a sad person (S), use the magic wand
   - Flip K consecutive people starting from current position

2. **State Tracking**
   - Keep track of how many times each position has been flipped
   - Use **difference array** or **flip counter** for efficiency
   - A position flipped even times = original state
   - A position flipped odd times = flipped state

3. **Validation**
   - After processing, check if all inhabitants are happy
   - If any sad person remains after the last possible wand use, return -1
   - Specifically, if there's a sad person at position > N - K + 1, it's impossible

4. **Optimization**
   - Use a running flip counter instead of actually flipping the array
   - For each position, calculate effective state based on total flips applied

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(T × N) |
| **Space** | O(N) |

**Where:**
- T = number of test cases
- N = number of inhabitants

---

## 🔑 Key Insights

- ✨ Use **greedy left-to-right** scan approach
- ✨ Always flip when encountering the **first sad person**
- ✨ Track flips using **difference array** or **flip counter** for efficiency
- ✨ If a sad person exists at position `i > N - K + 1`, it's **impossible** to make everyone happy
- ✨ Each position's final state depends on **total number of flips** affecting it
- ✨ **Minimum moves** achieved by processing left-to-right and only flipping when necessary
- ✨ Similar to **light bulb toggle** or **pancake flipping** problems

---

## 💡 Algorithm Steps
```
1. Initialize flip_counter = 0, total_wands = 0
2. For each position i from 1 to N:
   a. Determine current state (original XOR flip_counter % 2)
   b. If current state is Sad:
      - If i + K - 1 > N: return -1 (impossible)
      - Use wand at position i
      - Increment total_wands
      - Update flip tracking
3. Return total_wands
```

---

## 📚 Related Topics

- Greedy Algorithms
- Array Manipulation
- Difference Array
- Bit Manipulation
- Toggle/Flip Problems
- State Tracking

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>