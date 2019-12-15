const int MOD = 1e9+7;

/*
    https://leetcode.com/problems/k-inverse-pairs-array/

    Solution 1
    Time: O(N * K)
    Space: O(K)
*/

class Solution {
public:
    
    void add(int& a, int b) {
        a += b;
        if (a >= MOD) a -= MOD;
    }
    
    void sub(int& a, int b) {
        a -= b;
        if (a < 0) a += MOD;
    }
    
    int kInversePairs(int n, int k) {
        
        vector<int> dp(k + 1);
        dp[0] = 1;

        for (int i = 1; i <= n; i++) {
                      
            vector<int> dp_pref(dp);
            for (int j = 1; j <= k; j++) add(dp_pref[j], dp_pref[j - 1]);
            
            vector<int> new_dp(k + 1);
            new_dp[0] = 1;
            
            for (int j = 1; j <= k; j++) {
                int L = max(0, j - i + 1), R = j;
                
                new_dp[j] = dp_pref[R];
                if (L > 0) sub(new_dp[j], dp_pref[L - 1]);
                
            }           
            
            dp = new_dp;            
        }
        
        return dp[k];    
    }
};

/*

    Solution 2
    Time: O(N * K)
    Space: O(N * K)

*/

class Solution {
public:
    
    void add(int& a, int b) {
        a += b;
        if (a >= MOD) a -= MOD;
    }
    
    void sub(int& a, int b) {
        a -= b;
        if (a < 0) a += MOD;
    }
    
    int kInversePairs(int n, int k) {
        
        vector<vector<int>> dp(n + 1, vector<int>(k + 1));
        
        for (int i = 1; i <= n; i++) dp[i][0] = 1;
        
        for (int i = 2; i <= n; i++) {
            
            for (int j = 1; j <= k; j++) add(dp[i - 1][j], dp[i - 1][j - 1]);
            
            for (int j = 1; j <= k; j++) {
                int L = max(0, j - i + 1), R = j;
                
                dp[i][j] = dp[i - 1][R];
                if (L > 0) sub(dp[i][j], dp[i - 1][L - 1]);
            }
        }
        
        return dp[n][k];        
    }
};

/*
    Solution 3
    Time: O(N^2 * K)
    Space: O(N * K)

*/

class Solution {
public:
    
    void add(int& a, int b) {
        a += b;
        if (a >= MOD) a -= MOD;
    }
    
    int kInversePairs(int n, int k) {
        
        vector<vector<int>> dp(n + 1, vector<int>(k + 1));
        
        for (int i = 1; i <= n; i++) dp[i][0] = 1;
        
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= k; j++) {
                
                for (int new_inv = 0; new_inv < i; new_inv++) {
                    if (new_inv <= j) {
                        add(dp[i][j], dp[i - 1][j - new_inv]);
                    }
                }                
            }
        }
        
        return dp[n][k];        
    }
};