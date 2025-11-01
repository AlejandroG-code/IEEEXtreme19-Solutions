#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

// Compute G_k(T) for all k=1..K given the positions P where A[i] >= T.
// Formula: sum_{j=1..m-k+1} (P[j]-P[j-1]) * (N - P[j+k-1] + 1), with P[0]=0.
static inline void accumulate_Gk(const vector<int>& pos, int n, int K, vector<long long>& G) {
    int m = (int)pos.size();
    if (m == 0) return;
    // 1-indexed convenience with sentinel P[0]=0
    vector<int> P(m + 1);
    P[0] = 0;
    for (int i = 1; i <= m; ++i) P[i] = pos[i - 1];

    int maxK = min(K, m);
    for (int k = 1; k <= maxK; ++k) {
        long long sum = 0;
        // j runs 1..m-k+1
        for (int j = 1; j + k - 1 <= m; ++j) {
            long long leftChoices  = (long long)P[j] - (long long)P[j - 1];
            long long minRight     = (long long)P[j + k - 1];
            long long rightChoices = (long long)n - minRight + 1;
            sum += leftChoices * rightChoices;
        }
        G[k] += sum;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    if (!(cin >> N >> K)) return 0;
    vector<int> A(N);
    int maxA = 0;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        if (A[i] > maxA) maxA = A[i];
    }

    // Precompute bit thresholds 2^b
    int Bmax = 0;
    while ((1LL << (Bmax + 1)) <= maxA) ++Bmax; // floor(log2(maxA))
    // We need b from 0..Bmax (T=2^b) and U=2^{b+1}; note b=0 contributes 0 weight anyway.

    vector<long long> S(K + 1, 0);     // answers S_k, k=1..K
    vector<long long> G1(K + 1), G2(K + 1);

    for (int b = 0; b <= Bmax; ++b) {
        int T  = 1 << b;
        int U  = (b == 30 ? INT_MAX : (1 << (b + 1))); // safe, but maxA<=1e6

        // Build positions where A[i] >= T and >= U
        vector<int> posT, posU;
        posT.reserve(N);
        posU.reserve(N);
        for (int i = 0; i < N; ++i) {
            if (A[i] >= T) posT.push_back(i + 1);   // 1-based positions
            if (A[i] >= U) posU.push_back(i + 1);
        }

        // Reset G1,G2 partials for this b
        fill(G1.begin(), G1.end(), 0);
        fill(G2.begin(), G2.end(), 0);

        // Compute G_k(T) and G_k(U)
        accumulate_Gk(posT, N, K, G1);
        accumulate_Gk(posU, N, K, G2);

        // Add contribution: b * (G_k(T) - G_k(U))
        if (b > 0) { // b=0 contributes 0 anyway
            for (int k = 1; k <= K; ++k) {
                S[k] += (long long)b * (G1[k] - G2[k]);
            }
        }
    }

    // Print S1..SK
    for (int k = 1; k <= K; ++k) {
        if (k > 1) cout << ' ';
        cout << S[k];
    }
    cout << '\n';
    return 0;
}
