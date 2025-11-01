#include <bits/stdc++.h>
using namespace std;

// --- choose the rounding used by YOUR judge ---
// #define ROUND_CEIL_TWO_DEC          // uncomment if judge wants ceiling to 2 decimals
#define ROUND_NEAREST_TWO_DEC          // comment this if you use CEIL

static inline long long ipow_ll(long long a, int k){
    long long r = 1;
    while (k--) r *= a;                // K <= 6, a <= 1023 => fits in int64
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K; 
    if(!(cin >> N >> K)) return 0;

    // Build XOR-basis for values < 1024 (10 bits: 0..9)
    int basis[10] = {0};
    for (int i = 0; i < N; ++i) {
        int x; cin >> x;
        for (int b = 9; b >= 0; --b) {
            if (((x >> b) & 1) == 0) continue;
            if (!basis[b]) { basis[b] = x; break; }   // new pivot
            x ^= basis[b];                            // eliminate bit b
        }
    }

    // Collect independent generators (unique MSBs guarantee independence)
    vector<int> gen;
    for (int b = 9; b >= 0; --b) if (basis[b]) gen.push_back(basis[b]);

    // Enumerate the span: start with {0} and double each time
    vector<int> span = {0};
    for (int v : gen) {
        int sz = (int)span.size();
        span.reserve(sz * 2);
        for (int i = 0; i < sz; ++i) span.push_back(span[i] ^ v);
    }

    // Exact sum of x^K in 128-bit
    __int128 sum = 0;
    for (int x : span) sum += (__int128)ipow_ll(x, K);

    long long den = (long long)span.size();           // = 2^rank, at least 1
    __int128 num100 = sum * 100;                      // work in cents

    long long cents;
#ifdef ROUND_CEIL_TWO_DEC
    // ceil(num100 / den)
    cents = (long long)((num100 + (den - 1)) / den);
#else
    // round to nearest (half up). All values non-negative.
    cents = (long long)((num100 + den / 2) / den);
#endif

    // Print exactly two decimals, no locale surprises
    long long whole = cents / 100, frac = cents % 100;
    cout << whole << '.';
    if (frac < 10) cout << '0';
    cout << frac << '\n';
    return 0;
}
