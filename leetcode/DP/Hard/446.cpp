/*
    https://leetcode.com/problems/arithmetic-slices-ii-subsequence/

    Time: O(N^2)
    Space: O(N^2)

*/

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int n = A.size();
        
        vector<unordered_map<long long, long long>> dp(n);
        // dp[i][diff] = no. of subsequences ending at index i with common difference 'diff'
        
        long long ans = 0;
        
        for (int i = 0; i < n; i++) {
            
            for (int j = 0; j < i; j++) {
                
                long long diff = (long long)A[i] - A[j];
                
                dp[i][diff] += 1;
                
                dp[i][diff] += dp[j][diff];                             
            }
            
            // add all the sequences ending at index i to final answer
            for (auto& it : dp[i]) {
                ans += it.second;
            }            
        }
        
        ans -= n*(n-1)/2; // removing length 2 sequences
        
        return ans;
    }
};