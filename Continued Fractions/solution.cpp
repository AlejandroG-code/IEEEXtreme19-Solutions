#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;

// Función rápida de inverso modular
ll modinv(ll x) {
    ll res = 1, e = MOD - 2;
    while(e) {
        if(e & 1) res = res * x % MOD;
        x = x * x % MOD;
        e >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<ll> num(N), den(N,1); // cada S_i como fracción num/den
    for(int i=0;i<N;i++) cin >> num[i];

    for(int q=0;q<M;q++){
        int op;
        cin >> op;
        if(op==1){
            ll X; cin >> X;
            // Operación add X
            for(int i=0;i<N;i++)
                num[i] = (num[i] + X * den[i]) % MOD;
        } else {
            // Operación invert
            for(int i=0;i<N;i++)
                swap(num[i], den[i]);
        }

        // Calcular suma total
        ll total_num = 0, total_den = 0;
        for(int i=0;i<N;i++){
            total_num = (total_num + num[i]) % MOD;
            total_den = (total_den + den[i]) % MOD;
        }

        ll ans = total_num * modinv(total_den) % MOD;
        cout << ans << "\n";
    }
}
