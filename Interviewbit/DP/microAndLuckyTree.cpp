/*
    https://www.hackerearth.com/practice/algorithms/dynamic-programming/bit-masking/practice-problems/algorithm/micro-and-lucky-tree/description/
    Time: O(N*M)
    Space: O(N*2^10)

*/

const int MOD = 1e9+7;
int n, m;
vector<vector<int>> adj;
vector<vector<int>> dp;
vector<int> p = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};// 10 primes <= 30
vector<int> has; // has[i] -> mask of all primes which divides i

void add(int& a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int mul(int a, int b) {
    return (a * 1LL * b) % MOD;
}

int dfs(int u, int pa, int mask) {
    int& ans = dp[u][mask];
    if (ans != -1) return ans;
    
    ans = 0;
    
    for (int val = 1; val <= m; val++) {
        bool leaf = 1;
        int ways = 1;
        for (int v : adj[u]) if (v != pa) {
            leaf = 0;
            ways = mul(ways, dfs(v, u, mask & has[val]));
        }
        if (leaf){
            if ((mask & has[val]) == 0) add(ans, 1);
        } 
        else add(ans, ways);
    }
    
    return ans;
}

int Solution::solve(int A, int B, vector<int> &C) {
    n = A;
    m = B;
    adj = vector<vector<int>>(n + 1);
    
    for (int i = 1; i < n; i++) {
        adj[i + 1].push_back(C[i]);
        adj[C[i]].push_back(i + 1);
    }
    
    has = vector<int>(m + 1);
    for (int i = 0; i < 10; i++) {
        for (int val = 1; val <= m; val++) {
            if (val % p[i] == 0) has[val] |= (1 << i);
        }
    }
    
    dp = vector<vector<int>>(n + 1, vector<int>((1 << 10), -1));
    
    int ans = dfs(1, 0, (1 << 10) - 1);
    
    return ans;
}
