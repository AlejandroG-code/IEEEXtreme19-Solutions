#include <bits/stdc++.h>
using namespace std;

static const int N = 1'000'000;

// Query over semiprime-index space
struct Q {
    int l, r, id, block;
    bool operator<(const Q& o) const {
        if (block != o.block) return block < o.block;
        // odd-even trick to reduce moves
        return (block & 1) ? (r > o.r) : (r < o.r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // -------- Sieve primes up to N --------
    vector<int> spf(N + 1, 0);
    vector<int> primes;
    primes.reserve(80000);

    for (int i = 2; i <= N; ++i) {
        if (!spf[i]) { spf[i] = i; primes.push_back(i); }
        for (int p : primes) {
            long long x = 1LL * p * i;
            if (p > spf[i] || x > N) break;
            spf[x] = p;
        }
    }
    auto isPrime = [&](int x) -> bool { return x >= 2 && spf[x] == x; };

    // -------- Build semiprimes list S and their two prime factors --------
    // S[i] is a semiprime value, fac1[i], fac2[i] are its prime factors (fac2=0 if square)
    vector<int> Svals;
    vector<int> fac1, fac2;
    Svals.reserve(220000);
    fac1.reserve(220000);
    fac2.reserve(220000);

    // Enumerate semiprimes p*q with p<=q
    for (int i = 0; i < (int)primes.size(); ++i) {
        int p = primes[i];
        long long p2 = 1LL * p * p;
        if (p2 > N) break;
        for (int j = i; j < (int)primes.size(); ++j) {
            int q = primes[j];
            long long v = 1LL * p * q;
            if (v > N) break;
            Svals.push_back((int)v);
            fac1.push_back(p);
            fac2.push_back(p == q ? 0 : q);
        }
    }

    // Sort semiprimes (we built in nondecreasing already but be safe)
    vector<int> order(Svals.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b){ return Svals[a] < Svals[b]; });

    vector<int> S, F1, F2;
    S.resize(order.size()); F1.resize(order.size()); F2.resize(order.size());
    for (size_t k = 0; k < order.size(); ++k) {
        int idx = order[k];
        S[k]  = Svals[idx];
        F1[k] = fac1[idx];
        F2[k] = fac2[idx];
    }
    int Ssz = (int)S.size();

    // Map primes to dense indices [0..Pcnt)
    // (We can reuse "primes" vector; create position map)
    vector<int> pIndex(N + 1, -1);
    for (int i = 0; i < (int)primes.size(); ++i) pIndex[primes[i]] = i;

    // -------- Read queries and map [L,R] to semiprime-index ranges --------
    int T;
    if (!(cin >> T)) return 0;
    vector<long long> ans(T, 0);
    vector<Q> qs; qs.reserve(T);

    auto lb = [&](int x){ return (int)(lower_bound(S.begin(), S.end(), x) - S.begin()); };
    auto rb = [&](int x){ return (int)(upper_bound(S.begin(), S.end(), x) - S.begin()) - 1; };

    const int B = max(1, (int)floor(sqrt(max(1, Ssz))));
    for (int i = 0; i < T; ++i) {
        int L, R; cin >> L >> R;
        int Lp = lb(L);
        int Rp = rb(R);
        if (Lp > Rp) {
            // no semiprimes in range
            ans[i] = 0;
            continue;
        }
        Q q;
        q.l = Lp; q.r = Rp; q.id = i; q.block = Lp / B;
        qs.push_back(q);
    }

    if (qs.empty()) {
        for (int i = 0; i < T; ++i) cout << ans[i] << '\n';
        return 0;
    }

    sort(qs.begin(), qs.end());

    // -------- Mo over semiprimes --------
    vector<int> cnt(primes.size(), 0);
    long long curAns = 0;
    int L = 0, R = -1;

    auto addIdx = [&](int idx){
        int p = F1[idx];
        int q = F2[idx];
        // update for p
        int ip = pIndex[p];
        curAns += cnt[ip];
        ++cnt[ip];
        // update for q if exists and distinct
        if (q) {
            int iq = pIndex[q];
            curAns += cnt[iq];
            ++cnt[iq];
        }
    };
    auto remIdx = [&](int idx){
        int p = F1[idx];
        int q = F2[idx];
        // remove p
        int ip = pIndex[p];
        --cnt[ip];
        curAns -= cnt[ip];
        // remove q if exists and distinct
        if (q) {
            int iq = pIndex[q];
            --cnt[iq];
            curAns -= cnt[iq];
        }
    };

    for (const auto& q : qs) {
        while (L > q.l) addIdx(--L);
        while (R < q.r) addIdx(++R);
        while (L < q.l) remIdx(L++);
        while (R > q.r) remIdx(R--);
        ans[q.id] = curAns;
    }

    // Fill zero-interval queries already set above
    for (int i = 0; i < T; ++i) cout << ans[i] << '\n';
    return 0;
}
