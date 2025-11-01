# 🎰 New Casino Game

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

The casinos in Las Vegas feel like people are not coming as much as they used to; they have a theory that it's because their games have gone stale. They have had the same games since forever! So they have come up with a new one.

This game is played on a **N × N** square board, where each tile is colored white or black as in chess, such that the most common color on the board is white. Here are examples of the boards for **N = 1, 2, 3, 4, 5**:
```
N=1:    N=2:    N=3:      N=4:        N=5:
□       □■      □■□       □■□■        □■□■□
        ■□      ■□■       ■□■□        ■□■□■
                □■□       □■□■        □■□■□
                          ■□■□        ■□■□■
                                      □■□■□
```

A player can come up and bet on the game; after that, **N** pieces will be put at random on the board, such that no two pieces are on the same row or column. The player will get **1 dollar** for each piece that is on a **white tile** and will **lose a dollar** for each piece that is on a **black tile**.

The casino has hired you to help them figure out what the expected amount of dollars they'll win is.

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `T` | Number of test cases |

For each test case:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `N` | Size of the chess board |

**Example Structure:**
```
T
N₁
N₂
...
Nₜ
```

---

## 📤 Output Format

Print **T** lines. On each one, an integer: the expected number of dollars the casino will have to pay to a player, taken modulo **998244353** (the answer can always be represented as an irreducible fraction **a/b**, where **b mod 998244353 ≠ 0**. You have to print **a · b⁻¹ mod 998244353**).

---

## 🔒 Constraints
```
1 ≤ T ≤ 10
1 ≤ N ≤ 10⁶
```

### ⏱️ Time and Memory Limits

- **Time limit:** 2000 ms
- **Memory limit:** 256 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This is a **probability** and **modular arithmetic** problem:

1. **Understanding the Board**
   - N×N chessboard with alternating colors
   - Top-left is white (like standard chess)
   - White tiles: positions where (i+j) is even
   - Black tiles: positions where (i+j) is odd

2. **Counting White Tiles**
   - For N×N board:
     - If N is odd: white tiles = ⌈N²/2⌉ = (N²+1)/2
     - If N is even: white tiles = N²/2

3. **Expected Value Calculation**
   - N pieces placed randomly (one per row, one per column)
   - This is a permutation problem
   - Expected whites = (number of white tiles / total tiles) × N
   - Expected value = Expected whites - (N - Expected whites)
   - = 2 × Expected whites - N

4. **Modular Arithmetic**
   - Use Fermat's Little Theorem for modular inverse
   - a/b mod p = a × b^(p-2) mod p (when p is prime)

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(T × log MOD) |
| **Space** | O(1) |

**Where:**
- T = number of test cases
- MOD = 998244353

---

## 🔑 Key Insights

- ✨ **White tile count:**
  - If N is odd: (N² + 1) / 2
  - If N is even: N² / 2
- ✨ **Expected whites** = (white_count × N) / N²
- ✨ **Expected blacks** = N - Expected whites
- ✨ **Expected profit** = Expected whites - Expected blacks = 2 × Expected whites - N
- ✨ Simplify: E = (2 × white_count × N / N²) - N = (2 × white_count / N) - N
- ✨ Use **modular inverse** for division
- ✨ Answer format: **a × b⁻¹ mod 998244353**

---

## 💡 Example Explanation

**Test Case 1: N = 5**
- Board is 5×5 = 25 tiles
- White tiles = (25 + 1) / 2 = 13
- Black tiles = 12
- 5 pieces placed randomly
- Expected whites = 13/5 per piece × 5 pieces = 13 (wait, this needs correction)

Actually, with N pieces placed such that no two are in same row/column:
- Each placement is a permutation
- Expected value calculation:
  - For each valid placement (permutation), count whites - blacks
  - Average over all N! permutations

**Simpler approach:**
- Expected whites per placement = (white_tiles / N²) × N = white_tiles / N
- Expected value = 2 × (white_tiles / N) - N

For N=5: white_tiles = 13
- E = 2 × 13/5 - 5 = 26/5 - 25/5 = 1/5
- Modular form: 1 × 5⁻¹ mod 998244353

---

## 🔍 Solution Formula
```python
MOD = 998244353

def mod_inverse(a, m):
    return pow(a, m - 2, m)

def solve(N):
    # Count white tiles
    if N % 2 == 1:
        white = (N * N + 1) // 2
    else:
        white = (N * N) // 2
    
    # Expected value = (2 * white - N * N) / N
    # Simplified: (2 * white - N^2) / N
    
    numerator = (2 * white - N * N) % MOD
    denominator = N % MOD
    
    result = (numerator * mod_inverse(denominator, MOD)) % MOD
    
    return result

T = int(input())
for _ in range(T):
    N = int(input())
    print(solve(N))
```

---

## 📚 Related Topics

- Probability Theory
- Expected Value
- Combinatorics
- Modular Arithmetic
- Modular Inverse
- Fermat's Little Theorem
- Permutations

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>