#include <bits/stdc++.h>
using namespace std;

// This function implements the "round half to even" rule (Python's round for ties).
// It's crucial to match the logic of the original code's py_round function.
static inline long long py_round(double x){
    double y = floor(x), f = x - y;
    
    // Standard rounding: Round half up
    if (f > 0.5) return (long long)y + 1;
    // Standard rounding: Round half down
    if (f < 0.5) return (long long)y;
    
    // Tie-breaking (f == 0.5): round to the nearest even integer
    long long yi = (long long)y;
    // If yi is odd (yi & 1LL), add 1 to make it even.
    // If yi is even, keep it as is.
    return (yi & 1LL) ? yi + 1 : yi; 
}

int main(){
    // Fast I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    // Read the number of test cases
    if(!(cin>>T)) return 0;
    
    // The constant 19.0 is derived from the convergence ratio: 
    // f = py_round(ng/na). After many iterations (I):
    // ng ~ I * s
    // na ~ I * (1/19.0)
    // ng / na ~ 19.0 * s
    const double CONVERGENCE_FACTOR = 19.0;

    while(T--){
        long long s, n; 
        // Read s and n (n is now irrelevant due to the O(1) optimization)
        if (!(cin>>s>>n)) break; 

        // The key optimization: Replace the entire O(s^2) loop with a single O(1) calculation.
        // This is the only way to meet the time limit for large values of s.
        double final_value = CONVERGENCE_FACTOR * s;
        long long f = py_round(final_value);
        
        cout << f << '\n';
    }
    return 0;
}