#include <iostream>
#include <vector>
using namespace std;

// 1. Top-Down DP (Memoization)
long long fibMemo(int n, vector<long long>& memo) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];

    return memo[n] = fibMemo(n - 1, memo) + fibMemo(n - 2, memo);
}

// 2. Bottom-Up DP (Tabulation)
long long fibTabulation(int n) {
    if (n <= 1) return n;
    vector<long long> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

int main() {
    int n = 40;

    // Memoization execution
    vector<long long> memo(n + 1, -1);
    long long memoResult = fibMemo(n, memo);

    // Tabulation execution
    long long tabResult = fibTabulation(n);

    cout << "==========================================" << endl;
    cout << "    FIBONACCI USING DYNAMIC PROGRAMMING   " << endl;
    cout << "==========================================" << endl;
    cout << "Target term (N)           : " << n << endl;
    cout << "1. Memoization Result     : " << memoResult << endl;
    cout << "2. Tabulation Result      : " << tabResult << endl;
    cout << "==========================================" << endl;

    return 0;
}
