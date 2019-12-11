
/*
    https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/

    Solution 1
    
    Time: O(N^2 * K)
    Space: O(N * K)


*/

class Solution {
public:
    
    int n;
    vector<int> prices;
    vector<vector<int>> dp;
    
    int go(int i, int k) {
        if (k == 0 || i < 0) return 0;
        
        int& ans = dp[i][k];
        
        if (ans != -1) return ans;
        
        ans = go(i - 1, k);
        
        for (int j = 0; j < i; j++) {
            if (prices[j] < prices[i]) ans = max(ans, go(j - 1, k - 1) + prices[i] - prices[j]);
        }
        
        return ans;
    }
    
    int easySolve() {
        
        int ans = 0;
        for (int i = 1; i < n; i++) {
            ans += max(0, prices[i] - prices[i - 1]);
        }
        
        return ans;
    }
    
    int maxProfit(int k, vector<int>& a) {
        prices = a;
        n = prices.size();
        
        if (n < 2) return 0;
        
        if (2 * k >= n) return easySolve();
        
        dp = vector<vector<int>>(n + 5, vector<int>(k + 5, -1));
        
        return go(n - 1, k);
    }
};


class Solution {
public:
    
    int n, k;
    vector<int> prices;
    vector<vector<int>> dp;
    
    int go() {
        
        for (int i = 1; i < n; i++) {           
            
            for (int j = 1; j <= k; j++) {
                dp[i][j] = dp[i - 1][j];
                
                for (int buy = 0; buy < i; buy++) {
                    dp[i][j] = max(dp[i][j], (buy > 0 ? dp[buy - 1][j - 1] : 0) + prices[i] - prices[buy]);
                }
                
            }
        }
        
        return dp[n - 1][k];
        
    }
    
    int easySolve() {
        
        int ans = 0;
        for (int i = 1; i < n; i++) {
            ans += max(0, prices[i] - prices[i - 1]);
        }
        
        return ans;
    }
    
    int maxProfit(int maxTrans, vector<int>& a) {
        prices = a;
        n = prices.size();
        
        if (n < 2) return 0;
        
        k = maxTrans;
        
        if (2 * k >= n) return easySolve();
        
        dp = vector<vector<int>>(n + 5, vector<int>(k + 5));
        
        return go();
    }
};

/*

    Solution 2

    Time: O(N*K)
    Space: O(N*K)


*/

class Solution {
public:
    
    int n, k;
    vector<int> prices;
    vector<vector<int>> dp;
    
    int go() {
        
        for (int j = 1; j <= k; j++) {           
            
            int max_dp = -prices[0];
            
            for (int i = 1; i < n; i++) {
                dp[i][j] = dp[i - 1][j];
                
                dp[i][j] = max(dp[i][j], prices[i] + max_dp); 
                // need max(dp[id][j-1] - prices[id+1]), 0 <= id < i which is kept in max_dp to avoid another loop 
                
                max_dp = max(max_dp, dp[i][j - 1] - prices[i]);
                
            }
        }
        
        return dp[n - 1][k];
        
    }
    
    int easySolve() {
        
        int ans = 0;
        for (int i = 1; i < n; i++) {
            ans += max(0, prices[i] - prices[i - 1]);
        }
        
        return ans;
    }
    
    int maxProfit(int maxTrans, vector<int>& a) {
        prices = a;
        n = prices.size();
        
        if (n < 2) return 0;
        
        k = maxTrans;
        
        if (2 * k >= n) return easySolve();
        
        dp = vector<vector<int>>(n + 5, vector<int>(k + 5));
        
        return go();
    }
};