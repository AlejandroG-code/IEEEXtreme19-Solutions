#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Array to define the 4 possible moves (up, down, left, right)
// dr[i] is the change in row index, dc[i] is the change in column index
int dr[] = {-1, 1, 0, 0}; // Row changes: Up, Down,
int dc[] = {0, 0, -1, 1}; // Col changes: Left, Right

// Global variables for convenience
int N, M;
vector<vector<int>> matrix;
// Memoization table: dp[r][c] stores the longest increasing path starting at (r, c)
vector<vector<int>> dp; 

/**
 * @brief Finds the longest increasing path starting from cell (r, c) using memoization.
 * @param r Current row index.
 * @param c Current column index.
 * @return The maximum length of the increasing path starting at (r, c).
 */
int solve(int r, int c) {
    // 1. Check memoization table
    if (dp[r][c] != 0) {
        return dp[r][c];
    }

    // 2. Base case: The path length is at least 1 (the cell itself)
    int max_path = 1;

    // 3. Check all 4 neighbors
    for (int i = 0; i < 4; ++i) {
        int next_r = r + dr[i];
        int next_c = c + dc[i];

        // Check if the neighbor is within bounds
        if (next_r >= 0 && next_r < N && next_c >= 0 && next_c < M) {
            
            // Check the increasing value condition: next cell must be greater
            if (matrix[next_r][next_c] > matrix[r][c]) {
                // The path can be extended through this neighbor.
                // max_path = 1 + longest path starting from the neighbor
                max_path = max(max_path, 1 + solve(next_r, next_c));
            }
        }
    }

    // 4. Memoize and return the result
    dp[r][c] = max_path;
    return max_path;
}

int main() {
    // Optimize input/output operations
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read matrix dimensions
    if (!(cin >> N >> M)) return 0;

    // Resize matrix and memoization table
    matrix.resize(N, vector<int>(M));
    dp.resize(N, vector<int>(M, 0)); // Initialize DP table with 0

    // Read matrix values
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> matrix[i][j];
        }
    }

    // The final answer is the maximum path length starting from ANY cell.
    int overall_max_length = 0;

    // Iterate through every cell and compute the max path starting from it
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            overall_max_length = max(overall_max_length, solve(i, j));
        }
    }

    // Output the final result
    cout << overall_max_length << endl;

    return 0;
}