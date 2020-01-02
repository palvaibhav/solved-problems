/*
    Time:O((1<<N)*N)
    Space:O((1<<N))

*/

int n;
vector<int> cantHave;
vector<long long> dp;

long long go(int mask) {
    if (__builtin_popcount(mask) == n) return 1;
    long long& ans = dp[mask];
    if (ans != -1) return ans;
    ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!(mask & (1 << (i - 1)))) {
            if (mask & cantHave[i]) continue;
            ans += go(mask | (1 << (i - 1)));
        }
    }
    return ans;
}

string Solution::solve(int A) {
    n = A;
    
    cantHave = vector<int>(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if ((j & i) == j) cantHave[j] |= (1 << (i - 1));
        }
    }

    dp = vector<long long>(1 << n, -1);
    long long ans = go(0);
    
    return to_string(ans);
}
