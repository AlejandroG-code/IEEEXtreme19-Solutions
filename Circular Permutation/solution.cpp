#include <bits/stdc++.h>
using namespace std;

static int MinRadius(vector<int> a, int N){
    sort(a.begin(), a.end());
    int max_gap = 0;
    for (int i = 0; i + 1 < N; ++i)
        max_gap = max(max_gap, a[i+1] - a[i]);
    // wrap gap
    max_gap = max(max_gap, a[0] + N - a.back());

    int L = N - max_gap;            // minimal covering arc length (in steps)
    int D = (L + 1) / 2;            // ceil(L/2)
    return D;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; 
    if (!(cin >> N)) return 0;
    vector<int> p(N);
    for (int i = 0; i < N; ++i) cin >> p[i];

    // pos[x] = index of friend x (1..N) at the table
    vector<int> pos(N+1);
    for (int i = 0; i < N; ++i) pos[p[i]] = i;

    vector<int> sinc(N), sdec(N);
    for (int x = 1; x <= N; ++x){
        int i = x - 1;
        int a = pos[x] - i;             // for increasing
        int b = pos[x] + i;             // for decreasing
        // normalize to [0..N-1]
        a %= N; if (a < 0) a += N;
        b %= N; if (b < 0) b += N;
        sinc[i] = a;
        sdec[i] = b;
    }

    int ans = min(MinRadius(sinc, N), MinRadius(sdec, N));
    cout << ans << '\n';
    return 0;
}
