#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1'000'000'007;

// combine (mod)
inline void addmod(int &a, int b) { int s=a+b; if(s>=MOD) s-=MOD; a=s; }

// count #tuples with a^b^c^d == 0 and Ai <= xi <= Bi
int count_xor_zero(uint64_t A[4], uint64_t B[4]) {
    // dp[state], state has 8 bits: for v=0..3, bit(2*v)=lo_tight, bit(2*v+1)=hi_tight
    static int dp[256], ndp[256];
    memset(dp, 0, sizeof(dp));
    // start: all tight
    int ALLTIGHT = 0;
    for (int v=0; v<4; ++v) ALLTIGHT |= (1<<(2*v)) | (1<<(2*v+1));
    dp[ALLTIGHT] = 1;

    // precompute the 8 masks with even parity on 4 bits
    static int evenMasks[8]; static bool inited=false;
    if (!inited) {
        int k=0;
        for (int m=0;m<16;++m) if (__builtin_parity((unsigned)m)==0) evenMasks[k++]=m;
        inited=true;
    }

    for (int bit=60; bit>=0; --bit) {
        memset(ndp, 0, sizeof(ndp));
        uint64_t abit[4], bbit[4];
        for (int v=0; v<4; ++v) {
            abit[v] = (A[v]>>bit)&1ULL;
            bbit[v] = (B[v]>>bit)&1ULL;
        }
        for (int s=0; s<256; ++s) {
            int cur = dp[s];
            if (!cur) continue;

            for (int maskIdx=0; maskIdx<8; ++maskIdx) {
                int m = evenMasks[maskIdx];
                int ns = 0;
                bool ok = true;

                for (int v=0; v<4; ++v) {
                    int x = (m>>v)&1;              // chosen bit for variable v
                    int lo = (s>>(2*v))&1;
                    int hi = (s>>(2*v+1))&1;
                    uint64_t av = abit[v], bv = bbit[v];

                    // lower bound check (still tight -> must x >= av)
                    if (lo && x < (int)av) { ok=false; break; }
                    // upper bound check (still tight -> must x <= bv)
                    if (hi && x > (int)bv) { ok=false; break; }

                    int nlo = lo && (x==(int)av);
                    int nhi = hi && (x==(int)bv);
                    if (nlo) ns |= 1<<(2*v);
                    if (nhi) ns |= 1<<(2*v+1);
                }
                if (ok) addmod(ndp[ns], cur);
            }
        }
        memcpy(dp, ndp, sizeof(dp));
    }

    int sum = 0;
    for (int s=0;s<256;++s) addmod(sum, dp[s]);
    return sum;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q; 
    if(!(cin>>Q)) return 0;

    while(Q--){
        uint64_t A[4], B[4];
        for (int i=0;i<4;++i){
            cin>>A[i]>>B[i];
        }

        // total tuples
        long long tot = 1;
        for (int i=0;i<4;++i){
            long long add = ( (__int128)(B[i] - A[i] + 1) ) % MOD;
            tot = (tot * add) % MOD;
        }

        int zero = count_xor_zero(A,B);
        int ans = ( (tot - zero) % MOD + MOD ) % MOD;
        cout << ans << '\n';
    }
    return 0;
}
