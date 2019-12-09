/*
    https://leetcode.com/problems/longest-valid-parentheses/

    Time: O(N)
    Space: O(N)

*/

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        
        vector<int> dp(n);
        
        stack<int> stk;
        
        int ans = 0;
        
        for (int i = 0; i < n; i++) {
            
            if (s[i] == '(') {
                stk.push(i);
            }
            else {
                if (stk.empty()) {
                    stk.push(i);
                } else {
                   int L = stk.top();
                   if (s[L] == '(') {
                       dp[i] = i - L + 1;
                       
                       if (L > 0) dp[i] += dp[L - 1];
                       
                       stk.pop();
                   } else {
                       stk.push(i);
                   }
                }
            }
            
            ans = max(ans, dp[i]);            
        }
        
        return ans;
    }
};