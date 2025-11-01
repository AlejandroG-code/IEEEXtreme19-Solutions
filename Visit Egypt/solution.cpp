#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1'000'000'007;
int addmod(long long x){ x%=MOD; if(x<0) x+=MOD; return int(x); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    if(!(cin >> T)) return 0;
    vector<int> N(T);
    vector<int> M(T), A(T);
    int maxN = 0;
    for (int i = 0; i < T; ++i){
        cin >> N[i] >> M[i] >> A[i];
        maxN = max(maxN, N[i]);
    }

    // target in 25-piastre units: t = 212 * N
    const int UNIT_PER_EURO = 212;
    int maxT = UNIT_PER_EURO * maxN;

    // denominations in units of 25 piastres
    const int D[9] = {1,2,4,20,40,80,200,400,800};

    vector<int> f(maxT + 1, 0);
    f[0] = 1;
    for (int i = 1; i <= maxT; ++i){
        long long sum = 0;
        // only 9 terms; do a tight loop without modulo until the end
        if (i >= 1)   sum += f[i-1];
        if (i >= 2)   sum += f[i-2];
        if (i >= 4)   sum += f[i-4];
        if (i >= 20)  sum += f[i-20];
        if (i >= 40)  sum += f[i-40];
        if (i >= 80)  sum += f[i-80];
        if (i >= 200) sum += f[i-200];
        if (i >= 400) sum += f[i-400];
        if (i >= 800) sum += f[i-800];
        f[i] = int(sum % MOD);
    }

    auto decide = [&](int realv, int m, int a)->string{
        if (m == realv && a == realv) return "TIE";
        if (m == realv) return "Mikel";
        if (a == realv) return "Andrew";
        long long dm = llabs( (long long)realv - (long long)m );
        long long da = llabs( (long long)realv - (long long)a );
        if (dm < da) return "Mikel";
        if (da < dm) return "Andrew";
        return "NONE";
    };

    for (int i = 0; i < T; ++i){
        int t = UNIT_PER_EURO * N[i];
        int ans = f[t]; // already modulo 1e9+7
        cout << decide(ans, M[i], A[i]) << "\n";
    }
    return 0;
}
