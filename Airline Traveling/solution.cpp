#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const long long INFLL = (ll)4e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; ll k;
    if (!(cin >> N >> k)) return 0;

    vector<int> C(N, 0);
    for (int i = 1; i < N; ++i) cin >> C[i];

    int Q; 
    cin >> Q;

    // N == 1: only city 0 exists; only possible path is staying at 0 costing 0.
    if (N == 1) {
        while (Q--) {
            int A, B; cin >> A >> B;
            cout << ((A == 0 && B == 0 && k == 0) ? "Yes\n" : "No\n");
        }
        return 0;
    }

    // Build unique loop lengths v = 2*Ci (Ci in [1..1000])
    vector<char> seen(1001, 0);
    vector<int> loops; loops.reserve(1000);
    for (int i = 1; i < N; ++i) if (!seen[C[i]]) {
        seen[C[i]] = 1;
        loops.push_back(2 * C[i]);
    }

    // gcd of loop lengths
    int g = 0;
    for (int v : loops) g = std::gcd(g, v);

    // Dijkstra on residues mod g
    vector<ll> dist(g, INFLL);
    using P = pair<ll,int>;
    priority_queue<P, vector<P>, greater<P>> pq;
    dist[0] = 0;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, r] = pq.top(); pq.pop();
        if (d != dist[r]) continue;
        for (int v : loops) {
            int nr = (r + v) % g;
            ll nd = d + v;
            if (nd < dist[nr]) {
                dist[nr] = nd;
                pq.push({nd, nr});
            }
        }
    }

    auto achievable = [&](ll extra)->bool {
        if (extra < 0) return false;
        int r = (int)(extra % g);
        return dist[r] <= extra;
    };

    while (Q--) {
        int A, B; cin >> A >> B;
        bool ok = false;

        if (A == B) {
            if (A == 0) {                    // start & end at 0
                ok = achievable(k);          // includes k = 0 via dist[0]=0
            } else {                         // start & end at same leaf A
                if (k == 0) ok = true;       // take no flights at all
                else ok = (k >= 2LL*C[A]) && achievable(k - 2LL*C[A]);
            }
        } else { // A != B
            if (A == 0) {
                ok = (k >= C[B]) && achievable(k - C[B]);
            } else if (B == 0) {
                ok = (k >= C[A]) && achievable(k - C[A]);
            } else {
                ll base = (ll)C[A] + C[B];
                ok = (k >= base) && achievable(k - base);
            }
        }

        cout << (ok ? "Yes\n" : "No\n");
    }

    return 0;
}

