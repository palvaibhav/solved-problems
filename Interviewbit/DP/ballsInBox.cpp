/*

 Time:O(N*(1<<10))
 Space:O(N*(1<<10))

*/

const long long INF = 1e14;
int n, maxBalls;
vector<int> cost;
vector<int> have;
vector<vector<long long>> dp;

long long go(int i, int mask) {
    if (mask == maxBalls) return 0;
    if (i == n) return INF;
    long long& ans = dp[i][mask];
    if (ans != -1) return ans;
    ans = min(go(i + 1, mask), cost[i] + go(i + 1, mask | have[i]));
    return ans;
}

int Solution::solve(vector<int> &A, vector<string> &B) {
    n = A.size();
    cost = A;
    maxBalls = 0;
    have.clear();
    
    for (int i = 0; i < n; i++) {
        int mask = 0;
        int m = B[i].size();
        for (int j = m - 1; j >= 0; j--) {
            if (B[i][j] == '1') {
                mask |= (1 << (m - j - 1));
            }
        }
        have.push_back(mask);
        maxBalls |= mask;
    }
    
    dp = vector<vector<long long>>(n, vector<long long>(1 << 10, -1));
    
    return go(0, 0);
}
