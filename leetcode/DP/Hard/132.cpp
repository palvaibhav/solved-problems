/*
    https://leetcode.com/problems/palindrome-partitioning-ii/

    Time: O(N^2)
    Space: O(N^2)

*/

class Solution {
public:
    
    int n;
    vector<int> dp;
    vector<vector<bool>> isPalindrome;
    string s;
    
    void expand(int l, int r) {
        
        while (0 <= l && r < n && s[l] == s[r]) {
            isPalindrome[l][r] = true;
            l--;
            r++;
        }
    }
    
    int go(int i) {
        if (isPalindrome[i][n - 1]) return 0;
        
        int& ans = dp[i];
        if (ans != -1) return ans;
        
        ans = n + 1;
        
        for (int j = i; j < n - 1; j++) {
            if (isPalindrome[i][j]) {
                ans = min(ans, 1 + go(j + 1));
            }
        }
        
        return ans;
    }
    
    int minCut(string str) {
        s = str;
        n = s.size();
        
        isPalindrome = vector<vector<bool>>(n, vector<bool>(n));
        
        for (int i = 0; i < n; i++) {
            isPalindrome[i][i] = true;
            expand(i - 1, i + 1); // odd len
            expand(i, i + 1);     // even len
        }
        
        dp = vector<int>(n, -1);
        
        return go(0);
                
    }
};