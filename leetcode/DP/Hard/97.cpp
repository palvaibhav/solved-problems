/*
    https://leetcode.com/problems/interleaving-string/

    Time: O(N*M)
    Space: O(N*M)

*/

class Solution {
public:
    
    int go(int i, int j, string& s1, string& s2, string& s3, vector<vector<int>>& dp) {
        if (i < 0 && j < 0) return 1;
        else if (i < 0) {
            
            return s2.substr(0, j + 1) == s3.substr(0, j + 1);
                        
        } else if (j < 0) {
            
            return s1.substr(0, i + 1) == s3.substr(0, i + 1);
                        
        } else {
            
            int& ans = dp[i][j];
            
            if (ans != -1) return ans;
            
            ans = 0;
            
            int k = i + j + 1;
            
            if (s3[k] == s1[i]) ans |= go(i - 1, j, s1, s2, s3, dp);
            
            if (s3[k] == s2[j]) ans |= go(i, j - 1, s1, s2, s3, dp);
            
            return ans;            
        }
    }
    
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.size();
        int m = s2.size();
        int k = s3.size();
        
        if (n + m != k) return false;
        
        vector<vector<int>> dp(n, vector<int>(m, -1));
        
        return go(n - 1, m - 1, s1, s2, s3, dp);
    }
};