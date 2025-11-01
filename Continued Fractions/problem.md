# ➗ Continued Fractions

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

Miguel is studying the behavior of some continued fractions.

A continued fraction **[A₁; A₂, ..., Aₖ]** represents the value:
```
A₁ + ─────────────1─────────────
     A₂ + ────────1────────
          ⋱ + ────1────
               Aₖ
```

Miguel starts with a sequence **S₁, S₂, ..., Sₙ**, where each **Sᵢ** represents a continued fraction value.

He then performs **M** global operations on this sequence:

- **Operation 1 X:** add **X** to all elements, that is, **Sᵢ ← Sᵢ + X** for **1 ≤ i ≤ N**
- **Operation 2:** invert all elements, that is, **Sᵢ ← 1/Sᵢ**

Miguel guarantees that all values will be invertible when this operation is applied.

After each operation, Miguel must print the sum of all current values:

**∑ᵢ₌₁ᴺ Sᵢ**

For simplicity, you must output the result modulo **998244353**.

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `N M` | Two integers: number of elements and number of operations |
| 2 | `S₁ S₂ ... Sₙ` | N integers representing the initial values of the sequence |
| 3 to M+2 | Operation | One operation per line |

**Operation Format:**
- **1 X:** add X to all elements
- **2:** invert all elements

---

## 📤 Output Format

Print **M** lines. The **j-th** line should contain the sum **∑ᵢ₌₁ᴺ Sᵢ** after applying the **j-th** operation, reduced modulo **998244353**.

---

## 🔒 Constraints
```
1 ≤ N ≤ 10⁵
1 ≤ M ≤ 6 × 10⁵
1 ≤ Sᵢ < 998244353 for all i = 1, ..., N
0 ≤ X < 998244353
```

### ⏱️ Time and Memory Limits

- **Time limit:** 4000 ms
- **Memory limit:** 256 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This problem requires **modular arithmetic** and **efficient batch operations**:

1. **Understanding Operations**
   - **Operation 1 (Add X):** Simple addition to all elements
   - **Operation 2 (Invert):** Requires modular inverse: Sᵢ⁻¹ mod 998244353

2. **Modular Inverse**
   - Use **Fermat's Little Theorem**: a⁻¹ ≡ aᵖ⁻² (mod p) for prime p
   - Or use **Extended Euclidean Algorithm**
   - p = 998244353 is prime

3. **Batch Operations**
   - **Add operation:** Sum increases by N × X
   - Track sum incrementally rather than recalculating

4. **Optimization**
   - Maintain running sum
   - For add: `sum = (sum + N * X) % MOD`
   - For invert: compute each inverse and sum

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(N + M × N) worst case, O(N × inversions) |
| **Space** | O(N) |

**Where:**
- N = number of elements
- M = number of operations

---

## 🔑 Key Insights

- ✨ Use **Fermat's Little Theorem** for modular inverse: a⁻¹ ≡ aᵖ⁻² (mod p)
- ✨ **Prime modulo** 998244353 allows efficient inversion
- ✨ **Batch addition** can be optimized: new_sum = (old_sum + N × X) % MOD
- ✨ **Inversion** requires computing each element individually
- ✨ Use **fast modular exponentiation** for computing inverses
- ✨ Track the sum incrementally to avoid recalculation
- ✨ All values are guaranteed to be **non-zero** when inversion is applied

---

## 💡 Example Explanation

**Initial sequence:** S = {1, 2, 3, 4, 5}

**After Operation 1 (add 4 to all):**
- S = {5, 6, 7, 8, 9}
- However, since these represent continued fractions, we need to interpret them as fraction values
- Sum = ... (calculated with modular arithmetic)

**After Operation 2 (invert):**
- S = {2, 3, 4, 5, 6} (represented as continued fractions after inversion)
- Sum = 20

---

## 📚 Related Topics

- Modular Arithmetic
- Modular Inverse
- Fermat's Little Theorem
- Fast Exponentiation
- Continued Fractions
- Number Theory
- Batch Operations

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>