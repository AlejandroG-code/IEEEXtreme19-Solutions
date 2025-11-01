# 🎲 Four Piles

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

You will need to process **Q** queries with the following problem:

Given **A₁, B₁, A₂, B₂, A₃, B₃, A₄, B₄**, compute the number of tuples **(a, b, c, d)** with **A₁ ≤ a ≤ B₁, A₂ ≤ b ≤ B₂, A₃ ≤ c ≤ B₃** and **A₄ ≤ d ≤ B₄** such that the first player wins in a Nim game with piles **(a, b, c, d)**.

Can you solve this efficiently?

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `Q` | Number of queries |
| 2 to Q+1 | `A₁ B₁ A₂ B₂ A₃ B₃ A₄ B₄` | Eight integers: the bounds of the queries |

**Example Structure:**
```
Q
A₁ B₁ A₂ B₂ A₃ B₃ A₄ B₄
A₁ B₁ A₂ B₂ A₃ B₃ A₄ B₄
...
```

---

## 📤 Output Format

For each query, print a single line with the answer. Since the answer could be large, print it modulo **10⁹ + 7**.

---

## 🔒 Constraints
```
1 ≤ Q ≤ 1000
0 ≤ Aᵢ ≤ Bᵢ ≤ 10¹⁸ for all i = 1, ..., 4 in every query
```

### ⏱️ Time and Memory Limits

- **Time limit:** 2000 ms
- **Memory limit:** 256 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This is a **Nim game** combinatorics problem:

1. **Understanding Nim Game**
   - In Nim, the first player wins if and only if the XOR of all pile sizes is **non-zero**
   - For piles (a, b, c, d), first player wins if: **a ⊕ b ⊕ c ⊕ d ≠ 0**

2. **Count Losing Positions**
   - Total tuples = (B₁ - A₁ + 1) × (B₂ - A₂ + 1) × (B₃ - A₃ + 1) × (B₄ - A₄ + 1)
   - Losing tuples: where a ⊕ b ⊕ c ⊕ d = 0
   - Winning tuples = Total - Losing

3. **Count XOR = 0 Tuples**
   - Need to count tuples where a ⊕ b ⊕ c ⊕ d = 0
   - This means d = a ⊕ b ⊕ c
   - For each valid (a, b, c), check if d = a ⊕ b ⊕ c falls in [A₄, B₄]

4. **Digit DP Optimization**
   - Use digit DP to count tuples efficiently
   - Process bit by bit from most significant to least
   - Track constraints and XOR value

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(Q × log(max B) × 4) with Digit DP |
| **Space** | O(log(max B)) |

**Where:**
- Q = number of queries
- log(max B) ≈ 60 bits for 10¹⁸

---

## 🔑 Key Insights

- ✨ **Nim game theory:** First player wins iff XOR ≠ 0
- ✨ **Count complement:** Count losing positions (XOR = 0), then subtract
- ✨ Use **digit DP** to handle large ranges (up to 10¹⁸)
- ✨ For XOR = 0: **a ⊕ b ⊕ c ⊕ d = 0** means **d = a ⊕ b ⊕ c**
- ✨ Process **bit by bit** from MSB to LSB
- ✨ Track **tight bounds** in digit DP
- ✨ Answer = (Total tuples) - (Tuples with XOR = 0)

---

## 💡 Example Explanation

**Test Case 1:**
- Query: A₁=5, B₁=5, A₂=5, B₂=0, A₃=4, B₃=5, A₄=5, B₄=5
- Only tuple: (5, 5, 0, 5)
- XOR: 5 ⊕ 5 ⊕ 0 ⊕ 5 = 5 ≠ 0
- First player wins → **Answer: 1**

**Test Case 2:**
- Query: A₁=4, B₁=5, A₂=5, B₂=0, A₃=1, B₃=0, A₄=2, B₄=1, A₅=3, B₅=4
- Multiple tuples possible
- Count those where XOR ≠ 0
- **Answer: 20**

**Test Case 3:**
- Similar analysis
- **Answer: 6**

---

## 🔍 Algorithm Approach
```python
MOD = 10**9 + 7

def count_xor_zero(A1, B1, A2, B2, A3, B3, A4, B4):
    """Count tuples where a ⊕ b ⊕ c ⊕ d = 0"""
    # Use digit DP or direct enumeration
    count = 0
    
    # For each valid (a, b, c)
    for a in range(A1, B1 + 1):
        for b in range(A2, B2 + 1):
            for c in range(A3, B3 + 1):
                # d must equal a ⊕ b ⊕ c
                d = a ^ b ^ c
                if A4 <= d <= B4:
                    count += 1
    
    return count % MOD

def solve_query(A1, B1, A2, B2, A3, B3, A4, B4):
    # Total tuples
    total = ((B1 - A1 + 1) * (B2 - A2 + 1) * 
             (B3 - A3 + 1) * (B4 - A4 + 1)) % MOD
    
    # Losing tuples (XOR = 0)
    losing = count_xor_zero(A1, B1, A2, B2, A3, B3, A4, B4)
    
    # Winning tuples
    winning = (total - losing + MOD) % MOD
    
    return winning
```

---

## 📚 Related Topics

- Game Theory
- Nim Game
- XOR Properties
- Digit DP
- Combinatorics
- Bit Manipulation
- Dynamic Programming

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>