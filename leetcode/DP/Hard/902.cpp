/*
    https://leetcode.com/problems/numbers-at-most-n-given-digit-set/

    Time: O(log10(N)^2 * m^3) ~ 10^5
    Space: O(log10(N) * m)    ~ 10^2

*/

class Solution {
public:
    
    // O(log10(N))
    vector<int> getDigits(int N) {
        vector<int> res = {0};
        
        while (N > 0) {
            res.push_back(N % 10);
            
            N /= 10;
        }
        
        reverse(res.begin() + 1, res.end());
        
        return res;
    }
    
    // O(log10(N) * m)
    int count(int len, int i, int m, vector<vector<int>>& dp) {
        if (len <= 0) return 0;
        if (len == 1) return 1;
        
        int& ans = dp[len][i];
        
        if (ans != -1) return ans;
        
        ans = 0;
        
        for (int j = 0; j < m; j++) {
            ans += count(len - 1, j, m, dp);
        }
        
        return ans;
    }
    
    
    int atMostNGivenDigitSet(vector<string>& D, int N) {
        vector<int> num = getDigits(N);
        int max_len = (int)num.size() - 1;
        
        int m = D.size();
        
        int ans = 0;
        
        vector<vector<int>> dp(max_len + 1, vector<int>(m, -1));
        
        // O((log10(N) * m)^2)
        for (int len = 1; len < max_len; len++) {            
            for (int i = 0; i < m; i++) {
                ans += count(len, i, m, dp);
            }            
        } 
        
        // till now counted all ints with length < max_len
        
        unordered_set<string> allowed(D.begin(), D.end());
        
        // O(log10(N)^2 * m^3)
        for (int pos = 1; pos <= max_len; pos++) {            
            for (int i = 0; i < m; i++) { 
                int digit = stoi(D[i]);
                
                if (digit < num[pos]) { // try to place ith allowed digit at 'pos' 
                    int rem_len = max_len - pos;
                    if (rem_len == 0) ans += 1;
                    else {
                        for (int j = 0; j < m; j++) {
                            ans += count(rem_len, j, m, dp); 
                            // add count of ints with length 'rem_len' ending with digit j
                        }
                    }
                }
            }    
            if (!allowed.count(to_string(num[pos]))) break; // if cur digit of N not allowed then break 
        }
        
        // till now every int < N has been considered and counted for
        //  now check N itself is a valid integer
        
        int valid = 1;        
        
        for (int pos = 1; pos <= max_len; pos++) {
            if (!allowed.count(to_string(num[pos]))) {
                valid = 0;
                break;
            }
        }
        
        ans += valid;
        
        return ans;
    }
};

/*

    Solution 2

    Time: O(log10(N) * m * loglog10(N))
    Space: O(m)

*/

class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& D, int N) {
        int m = D.size();
        
        string num = to_string(N);
        int max_len = num.size();
        
        int ans = 0;
        
        for (int len = 1; len < max_len; len++) {
            ans += pow(m, len);
        }
        
        unordered_set<char> allowed;
        
        for (int i = 0; i < m; i++) allowed.insert(D[i][0]);
        
        int valid = 1;
        
        for (int pos = 0; pos < max_len; pos++) {    
            
            for (int i = 0; i < m; i++) {     
                
                if (D[i][0] < num[pos]) ans += pow(m, max_len - pos - 1);                
            }
            
            if (!allowed.count(num[pos])) {
                valid = 0;
                break;            
            }
        }
        
        ans += valid;
        
        return ans;
    }
};