# 🔐 Secure Elliptic Curve Point Addition

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

You are implementing a cryptocurrency wallet that performs elliptic curve operations. Given an elliptic curve defined by **y² = x³ + ax + b (mod p)**, implement [point addition](https://en.wikipedia.org/wiki/Elliptic_curve_point_multiplication).

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `T` | Number of test cases |
| 2 to T+1 | `a b p x₁ y₁ x₂ y₂` | Seven integers: curve parameters, prime modulus, first point coordinates, and second point coordinates |

**Example Structure:**
```
T
a b p x₁ y₁ x₂ y₂
a b p x₁ y₁ x₂ y₂
...
```

**Where:**
- `a, b` = elliptic curve parameters
- `p` = prime modulus
- `(x₁, y₁)` = coordinates of the first point
- `(x₂, y₂)` = coordinates of the second point

---

## 📤 Output Format

For each test case, print a single line:

- ✅ If result is point at infinity: `POINT_AT_INFINITY`
- ✅ Otherwise: Two space-separated integers `x₃ y₃` which are the coordinates of the answer

---

## 🔒 Constraints
```
1 ≤ T ≤ 1000
11 ≤ p < 1000 (p is prime)
0 ≤ a < p
1 ≤ b < p
0 ≤ x₁, y₁, x₂, y₂ < p
```

### ⏱️ Time and Memory Limits

- **Time limit:** 2500 ms
- **Memory limit:** 256 MB

### Additional Notes

- All the points are guaranteed to be on the curve

---

## 🎓 Solution Approach

### Algorithm Strategy

This problem requires implementing **elliptic curve point addition**:

1. **Handle Special Cases**
   - If one point is the point at infinity, return the other point
   - If points are inverses of each other, return point at infinity

2. **Calculate Slope**
   - If P₁ ≠ P₂: slope λ = (y₂ - y₁) / (x₂ - x₁) mod p
   - If P₁ = P₂: slope λ = (3x₁² + a) / (2y₁) mod p (point doubling)

3. **Compute Result Point**
   - x₃ = λ² - x₁ - x₂ mod p
   - y₃ = λ(x₁ - x₃) - y₁ mod p

4. **Modular Arithmetic**
   - Use modular inverse for division operations
   - Apply Extended Euclidean Algorithm or Fermat's Little Theorem

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(T log p) |
| **Space** | O(1) |

**Where:**
- T = number of test cases
- p = prime modulus

---

## 🔑 Key Insights

- ✨ **Modular inverse** is crucial for division in modular arithmetic
- ✨ Use **Fermat's Little Theorem**: a⁻¹ ≡ aᵖ⁻² (mod p) for prime p
- ✨ Handle **point doubling** (P + P) separately from general addition
- ✨ Check for **point at infinity** when x₁ = x₂ but y₁ ≠ y₂
- ✨ All operations must be performed **modulo p**
- ✨ The elliptic curve form is **Weierstrass equation**

---

## 📚 Related Topics

- Elliptic Curve Cryptography
- Modular Arithmetic
- Number Theory
- Cryptography
- Modular Inverse
- Fermat's Little Theorem

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>