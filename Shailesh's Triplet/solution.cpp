#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;

    while (t--) {
        unsigned long long n;
        cin >> n;

        if (n & 1ULL) { cout << -1 << '\n'; continue; }
        if ((n & (n - 1)) == 0ULL) { cout << -1 << '\n'; continue; }

        unsigned long long h = n >> 1;      
        unsigned long long k = h & (~h + 1ULL);

        unsigned long long a = n + k;
        unsigned long long b = h - k;
        unsigned long long c = h;


        if (a != b && a != c && b != c &&
            a > 0 && b > 0 && c > 0 &&
            (a + b + c == 2 * n) &&
            ((a ^ b ^ c) == n)) {
            cout << a << ' ' << b << ' ' << c << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
    return 0;
}
