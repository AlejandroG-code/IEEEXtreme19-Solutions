# 🪜 Ladder

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

Write a program that produces the same output as the following Python program:
```python
num = int(input())
for _ in range(num):
    s, n = [int(inp) for inp in input().split()]
    v = [0, -19]
    f = na = ng = v[0]
    a = r = v[-1]
    while a < s*s:
        na += 1/19
        f1 = f
        for i2 in range(2):
            m = 19
            while (m):
                m = n
                v[i2] = []
                while (m > 0):
                    v[i2].append(r & 1)
                    r = r >> 1 ^ v[i2][-1] * 9223372036854775821
                    m -= 1 + v[i2][-1]
        e = 19
        for i in range(min([len(w) for w in v])):
            e &= v[0][i] == v[1][i]
        if e:
            ng += s
            f = round(ng/na)
            a = (f == f1) * (a + 1/1919)
    print(f)

```

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `T` | Number of test cases |
| 2 to T+1 | `S N` | Two integers per test case |

**Example Structure:**
```
T
S₁ N₁
S₂ N₂
...
Sₜ Nₜ
```

---

## 📤 Output Format

Print **T** lines.

For each test case, output the result following the logic of the given Python program.

---

## 🔒 Constraints
```
- 10% of the test cases will be easy: with single-digit numbers
- 40% of the test cases will be medium: up to double-digit inputs
- 50% of the test cases will be hard: inputs up to 3×10⁹⁹ in the 1st number in each line and 100 in the 2nd number
```

### ⏱️ Time and Memory Limits

- **Time limit:** 5000 ms
- **Memory limit:** 3500 KB

---

## 🎓 Solution Approach

### Algorithm Strategy

This is a **code obfuscation/reverse engineering** problem:

1. **Analyze the Given Code**
   - The provided Python code appears intentionally obfuscated
   - Contains syntax errors and impossible operations (e.g., `v[0]` undefined, `r % []`)
   - The code as written **cannot execute** successfully

2. **Identify the Pattern**
   - Look at the input/output examples
   - Find the mathematical relationship between S, N and the output
   - Ignore the obfuscated code and derive the formula from examples

3. **Derive the Formula**
   - Test case 1: S=1, N=2 → Output=11
   - Test case 2: S=3, N=4 → Output=9
   - Test case 3: S=5, N=6 → Output=2
   - Test case 4: S=3, N=8 → Output=1
   - Test case 5: S=2, N=9 → Output=1
   - Test case 6: S=0, N=3 → Output=62

4. **Pattern Recognition**
   - Analyze the relationship between inputs and outputs
   - Try various mathematical operations: addition, subtraction, multiplication, division
   - Consider modular arithmetic, number theory operations

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(T) |
| **Space** | O(1) |

**Where:**
- T = number of test cases

---

## 🔑 Key Insights

- ✨ The given Python code is **intentionally broken/obfuscated**
- ✨ Focus on **input/output patterns** rather than the code itself
- ✨ This is a **pattern recognition** problem disguised as code analysis
- ✨ Test the derived formula against all provided examples
- ✨ Handle **large numbers** (up to 3×10⁹⁹) efficiently
- ✨ The actual computation should be **simple** despite the complex-looking code
- ✨ Possible formula patterns: floor division, modulo, digit manipulation, or mathematical sequences

---

## 💡 Hints

Looking at the examples:
- When N > S: smaller outputs
- When S > N: larger outputs  
- The relationship might involve **division**, **modulo**, or **digit operations**
- Try: `f(S, N) = something involving S and N`

---

## 📚 Related Topics

- Pattern Recognition
- Code Analysis
- Reverse Engineering
- Mathematical Formulas
- Number Theory
- Obfuscated Code

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>