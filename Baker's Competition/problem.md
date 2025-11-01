# 🎂 Baker's Competition

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

Mr. Baker is well-known for his baking skills, especially for making sliced cakes. He is hosting a competition. However, this competition is not a direct cake-eating competition as everyone thought. To win the competition, you have to solve the puzzle given below:

Mr Baker will provide **N** cakes (unsliced) of unique sizes from **1 to N** and place them accordingly to their size. He will then choose a segment of the cakes and ask each competitor to solve the following problem:

- A competitor will choose two cakes from the segment
- The competitor will have to slice both cakes with the same slice size **p > 1**
- The slice size must be the same for all the slices
- **p** should be a prime number
- The number of slices of each cake should be a prime number

The competitor has to count the number of such pairs of cakes in the segment. Pair **(i, j)** is equivalent to pair **(j, i)**.

Mr Baker may ask to solve this puzzle for multiple segments. The winner of the competition will be the one who answers all the puzzles correctly, and they will receive all the unsliced cakes!

As a cake-lover, can you answer the questions Mr Baker is going to ask?

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `T` | Number of puzzles Mr Baker is going to ask |
| 2 to T+1 | `L R` | Two integers denoting the first cake size and the last cake size from Mr Baker's segment |

**Example Structure:**
```
T
L₁ R₁
L₂ R₂
...
Lₜ Rₜ
```

---

## 📤 Output Format

For each puzzle, print the number of pairs that fulfill Mr Baker's conditions.

---

## 🔒 Constraints
```
1 ≤ T ≤ 10³
N = 10⁶
1 ≤ L < R ≤ N
```

### ⏱️ Time and Memory Limits

- **Time limit:** 1500 ms
- **Memory limit:** 256 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This problem requires **number theory** and **prime factorization**:

1. **Understanding the Problem**
   - For each pair of cakes (i, j) where L ≤ i < j ≤ R
   - Find a prime p > 1 such that:
     - i/p is a prime (i is divisible by p, result is prime)
     - j/p is a prime (j is divisible by p, result is prime)
   - Count all such valid pairs

2. **Prime Factorization**
   - For each number n in range [L, R], find all prime divisors
   - For each prime divisor p of n, check if n/p is also prime
   - Store valid (n, p) combinations

3. **Grouping by Prime Divisor**
   - For each prime p, collect all numbers n in [L, R] where:
     - n is divisible by p
     - n/p is also prime
   - If k numbers share the same prime p, they form C(k, 2) = k(k-1)/2 pairs

4. **Optimization with Sieve**
   - Precompute all primes up to N using Sieve of Eratosthenes
   - For each number, quickly check primality
   - Use efficient prime factorization

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(N log log N) preprocessing + O(T × (R-L) × log N) per query |
| **Space** | O(N) |

**Where:**
- N = maximum cake size (10⁶)
- T = number of test cases
- R - L = range size per query

---

## 🔑 Key Insights

- ✨ Use **Sieve of Eratosthenes** to precompute all primes up to 10⁶
- ✨ For each number n, check all its prime divisors p where n/p is also prime
- ✨ Group numbers by their valid prime divisor **p**
- ✨ Count pairs using **combination formula**: C(k, 2) = k × (k - 1) / 2
- ✨ A number can contribute to multiple pairs if it has multiple valid prime divisors
- ✨ Precomputation is crucial for handling multiple test cases efficiently
- ✨ For each number n = p × q where both p and q are primes, it's a valid candidate

---

## 💡 Example Explanation

**Test Case 1:** L = 1, R = 100
- Pair (4, 6): p = 2, 4/2 = 2 (prime), 6/2 = 3 (prime) ✓
- Pair (4, 10): p = 2, 4/2 = 2 (prime), 10/2 = 5 (prime) ✓
- And so on...

**Test Case 2:** L = 1, R = 10
- (4, 6): p = 2 ✓
- (4, 10): p = 2 ✓
- (6, 9): p = 3, 6/3 = 2 (prime), 9/3 = 3 (prime) ✓
- (6, 10): p = 2 ✓

Total: 4 valid pairs

---

## 📚 Related Topics

- Number Theory
- Prime Numbers
- Sieve of Eratosthenes
- Prime Factorization
- Combinatorics
- Precomputation
- Range Queries

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>