# ➕ Easy Sum

<div align="center">

![IEEEXtreme Competition](https://csacademy.com/static/svg/XtremeLogo19.svg)

</div>

---

## 📋 Problem Description

Victor claims he knows everything about range maximums.

To challenge him, his teammate Miguel gives him a problem he might not be able to solve.

You are given a sequence of positive integers **A₁, A₂, ..., Aₙ** and an integer **K**.

For each **k = 1, 2, ..., K**, compute:

**Sₖ = ∑ᵢ:ⱼ<ᵢ<ₖ ⌊log₂(maxₖ(Aᵢ, Aᵢ₊₁, ..., Aⱼ))⌋ × (r - l + 1)**

where **maxₖ** denotes the k-th largest element in the range **(Aᵢ, Aᵢ₊₁, ..., Aⱼ)**,

and **is** is defined as 0 if the range contains fewer than **k** elements.

Will Victor be able to solve this problem? Can you?

---

## 📥 Input Format

The input consists of the following:

| Line | Content | Description |
|------|---------|-------------|
| 1 | `N K` | Two integers: length of sequence and parameter K |
| 2 | `A₁ A₂ ... Aₙ` | N positive integers representing the sequence |

**Example Structure:**
```
N K
A₁ A₂ A₃ ... Aₙ
```

---

## 📤 Output Format

Print **K** integers: the values **S₁, S₂, ..., Sₖ**.

---

## 🔒 Constraints
```
1 ≤ N ≤ 10⁵
1 ≤ K ≤ 20
1 ≤ Aᵢ ≤ 10⁶
```

### ⏱️ Time and Memory Limits

- **Time limit:** 1000 ms
- **Memory limit:** 256 MB

---

## 🎓 Solution Approach

### Algorithm Strategy

This is a **range query** problem with **k-th maximum** elements:

1. **Understanding the Formula**
   - For each k from 1 to K
   - Consider all subarrays [i, j]
   - Find the k-th largest element in that subarray
   - Add ⌊log₂(k-th_max)⌋ × (j - i + 1) to Sₖ
   - If subarray has fewer than k elements, contribute 0

2. **Naive Approach**
   - Enumerate all O(N²) subarrays
   - For each subarray, find k-th largest for all k
   - Time: O(N² × K × log N)

3. **Optimization Ideas**
   - Use segment trees or other data structures
   - Process all K values simultaneously
   - Use sliding window or divide-and-conquer

4. **Implementation Strategy**
   - For each subarray [i, j]:
     - Extract elements and sort (or use selection)
     - For each k ≤ length, compute contribution
     - Add to corresponding Sₖ

### 📈 Complexity Analysis

| Metric | Complexity |
|--------|-----------|
| **Time** | O(N² × K × log N) |
| **Space** | O(N) |

**Where:**
- N = length of sequence
- K = parameter (max 20)

---

## 🔑 Key Insights

- ✨ Need to process **all subarrays** [i, j] where 1 ≤ i ≤ j ≤ N
- ✨ For each subarray, find **k-th largest** element for all k
- ✨ Use **⌊log₂(value)⌋** which is the bit length - 1
- ✨ Multiply by **subarray length** (j - i + 1)
- ✨ K is small (≤ 20), so can process all k values together
- ✨ Can use **sorting** or **selection** algorithms for k-th element
- ✨ **Contribution:** ⌊log₂(k-th_max)⌋ × length

---

## 💡 Example Explanation

**Input:**
```
10 10
10 1 9 2 8 3 7 4 6 5
```

**For k=1 (maximum element in each subarray):**
- Subarray [1,1]: max=10, log₂(10)=3, contribution = 3 × 1 = 3
- Subarray [1,2]: max=10, log₂(10)=3, contribution = 3 × 2 = 6
- And so on...

**Output:** `619 522 384 272 202 134 76 36 10 0`

---

## 🔍 Algorithm Steps
```python
import math

def solve(N, K, A):
    S = [0] * K
    
    # Iterate through all subarrays
    for i in range(N):
        for j in range(i, N):
            # Extract subarray
            subarray = A[i:j+1]
            length = j - i + 1
            
            # Sort to find k-th largest
            sorted_sub = sorted(subarray, reverse=True)
            
            # For each k
            for k in range(1, min(K + 1, length + 1)):
                kth_max = sorted_sub[k - 1]
                log_val = int(math.log2(kth_max)) if kth_max > 0 else 0
                S[k - 1] += log_val * length
    
    return S[:K]

# Read input
N, K = map(int, input().split())
A = list(map(int, input().split()))

# Solve and print
result = solve(N, K, A)
print(' '.join(map(str, result)))
```

---

## 📚 Related Topics

- Range Queries
- k-th Order Statistics
- Sliding Window
- Logarithms
- Array Processing
- Sorting Algorithms
- Selection Algorithms

---

<div align="center">

**Problem from IEEEXtreme 19.0 Programming Competition**

⭐ Happy Coding! ⭐

</div>