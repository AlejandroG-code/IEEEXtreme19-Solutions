# 🏛️ Visit Egypt

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

Mikel and Andrew plan to visit Egypt and want to exchange their Euros into Egyptian Pounds. **1 Egyptian Pound** is divided into **100 Egyptian Piastres** and Egypt's currency denominations include **25** and **50 Piastre coins**, and **1, 5, 10, 20, 50, 100,** and **200 Pound notes**.

Upon exchanging their money, Mikel and Andrew decide to engage in a game where they predict the number of possible ways to convert their Euros into Egyptian currency.

However, since they know that the number of ways could be large, they will consider that value modulo **10⁹ + 7** in their guesses. For this, consider that **order does matter**, so using a coin of **50 Piastre** and then a note of **100 Pounds** is considered a different way than using first a note of **100 Pounds** and then a coin of **50 Piastre**.

Can you determine who wins the game?

**Note 1:** One Euro equals **53 Egyptian Pounds**.

**Note 2:** One Egyptian Pound equals **100 Egyptian Piastres**.

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `T` | Number of test cases |
| 2 to T+1 | `N M A` | Three integers: Euro amount, and predictions from Mikel and Andrew |

**Example Structure:**
```
T
N₁ M₁ A₁
N₂ M₂ A₂
...
Nₜ Mₜ Aₜ
```

---

## 📤 Output Format

For each test case, determine the winner of the game:

- If one prediction is **closer** to the actual number of combinations, print the name of the winner (`Mikel` or `Andrew`)
- If both predictions are **equally distant** from the actual number, print `NONE`
- If both predictions **match** the actual number, print `TIE`

---

## 🔒 Constraints
```
1 ≤ T ≤ 10⁵
1 ≤ N ≤ 10⁶
0 ≤ M, A < 10⁹ + 7
```

### ⏱️ Time and Memory Limits

- **Time limit:** 2000 ms
- **Memory limit:** 256 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This is a **coin change problem** with **ordered permutations**:

1. **Understanding the Problem**
   - Need to count **permutations** (order matters), not combinations
   - Denominations in Piastres: [25, 50, 100, 500, 1000, 2000, 5000, 10000, 20000]
   - 1 Euro = 53 Pounds = 5300 Piastres
   - Total to make: N × 5300 Piastres

2. **Dynamic Programming Approach**
   - Let dp[i] = number of ways to make i Piastres (considering order)
   - Base case: dp[0] = 1
   - Transition: For each amount i and each coin c:
     - If i >= c: dp[i] = (dp[i] + dp[i-c]) % MOD

3. **Ordered Coin Change**
   - Since order matters, this is a permutation problem
   - Standard DP: dp[amount] += dp[amount - coin] for all coins

4. **Winner Determination**
   - Calculate actual = dp[N × 5300]
   - Compare |actual - M| vs |actual - A|
   - Determine winner based on distances

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(T × N × D) where D is number of denominations |
| **Space** | O(N × 5300) |

**Where:**
- T = number of test cases
- N = number of Euros (max value 10⁶)
- D = 9 denominations

---

## 🔑 Key Insights

- ✨ **Order matters** - this is a permutation problem, not combination
- ✨ Convert everything to **Piastres** for simplicity
- ✨ 1 Euro = 53 Pounds = **5300 Piastres**
- ✨ Denominations in Piastres: **[25, 50, 100, 500, 1000, 2000, 5000, 10000, 20000]**
- ✨ Use **DP for ordered coin change** (permutations)
- ✨ All calculations must be done **modulo 10⁹ + 7**
- ✨ Compare **absolute distances** to determine winner
- ✨ Handle three cases: one winner, tie, or none

---

## 💡 Example Explanation

**Test Case 1:** N = 10, M = 10, A = 25
- Total = 10 × 5300 = 53000 Piastres
- Actual ways = 90479252 (mod 10⁹ + 7)
- |90479252 - 10| = 90479242
- |90479252 - 25| = 90479227
- Andrew's guess is closer → **Andrew wins**

**Test Case 2:** N = 1, M = 443443317, A = 300000
- Total = 5300 Piastres
- Actual ways = 443443317
- |443443317 - 443443317| = 0
- |443443317 - 300000| = 443143317
- Mikel's guess is exact → **Mikel wins**

---

## 🔍 DP Algorithm
```python
MOD = 10**9 + 7
denominations = [25, 50, 100, 500, 1000, 2000, 5000, 10000, 20000]

def count_ways(amount):
    dp = [0] * (amount + 1)
    dp[0] = 1
    
    for i in range(1, amount + 1):
        for coin in denominations:
            if i >= coin:
                dp[i] = (dp[i] + dp[i - coin]) % MOD
    
    return dp[amount]

# For N Euros
total_piastres = N * 5300
actual = count_ways(total_piastres)

# Determine winner
dist_M = abs(actual - M)
dist_A = abs(actual - A)

if dist_M < dist_A:
    print("Mikel")
elif dist_A < dist_M:
    print("Andrew")
elif dist_M == 0 and dist_A == 0:
    print("TIE")
else:
    print("NONE")
```

---

## 📚 Related Topics

- Dynamic Programming
- Coin Change Problem
- Permutations
- Modular Arithmetic
- Number Theory
- Combinatorics

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>