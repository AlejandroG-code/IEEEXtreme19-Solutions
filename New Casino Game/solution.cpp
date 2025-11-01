#include <bits/stdc++.h>
using namespace std;
const long long MOD = 998244353;

long long modpow(long long a,long long e){
    long long r=1%MOD;
    a%=MOD;
    while(e){
        if(e&1) r=r*a%MOD;
        a=a*a%MOD;
        e>>=1;
    }
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if(!(cin>>T)) return 0;
    while(T--){
        long long N; cin>>N;
        if(N%2==0) cout<<0<<'\n';
        else cout<<modpow(N,MOD-2)<<'\n';
    }
}
