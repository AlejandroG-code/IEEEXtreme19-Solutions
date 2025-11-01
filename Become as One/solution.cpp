#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

// Define a type alias for a 64-bit integer, essential for the large sums.
using ll = long long;

/**
 * @brief Solves the IEEE Xtreme "Become as One" problem using prefix sums of powers of two.
 * * The core principle is that the operation (X, X -> X+1) preserves the sum of 2^A_i.
 * 2^X + 2^X = 2 * 2^X = 2^(X+1).
 * The array can be reduced to a single element E if and only if the sum of 2^A_i 
 * for the subarray is equal to 2^E, i.e., the sum is a power of two.
 */
void solve() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N, Q;
    // Read N (array length) and Q (number of queries)
    if (!(std::cin >> N >> Q)) return;

    // A: The input array. We only need the values for the prefix sum calculation.
    std::vector<int> A(N);
    // P: The prefix sum array. P[i] stores the sum of 2^A[j] for j from 0 to i-1.
    // Size N+1 for 1-based indexing in prefix sum logic (P[0] = 0).
    std::vector<ll> P(N + 1, 0);

    // --- Step 1 & 2: Read array, compute 2^A_i, and build prefix sums ---
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];

        // Calculate 2^A_i. A[i] <= 30, so 2^A[i] fits in a regular 'int' or 'long long'.
        // Use 1LL << A[i] for an efficient power of two calculation as a long long.
        ll current_power = 1LL << A[i];
        
        // P[i+1] is the prefix sum up to the i-th element (0-indexed)
        P[i + 1] = P[i] + current_power;
    }

    // --- Step 3: Process Queries ---
    for (int k = 0; k < Q; ++k) {
        int L, R;
        // Read 1-based query bounds
        std::cin >> L >> R;

        // Calculate the range sum S = P[R] - P[L-1].
        // This is the sum of 2^A_i for the subarray A[L..R].
        ll S = P[R] - P[L - 1];

        // --- Step 4: Check if S is a power of two ---
        bool is_power_of_two = false;
        
        // 1. Must be greater than 0 (a non-empty subarray)
        // 2. The standard bitwise check: X & (X-1) is 0 iff X is a power of two.
        if (S > 0 && (S & (S - 1)) == 0) {
            is_power_of_two = true;
        }

        if (is_power_of_two) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }
}

int main() {
    solve();
    return 0;
}