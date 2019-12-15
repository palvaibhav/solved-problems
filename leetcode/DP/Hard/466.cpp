/*
    https://leetcode.com/problems/count-the-repetitions/

    Time: O(rep1 + M*N*(M+N)) ~ 10^6
    Space: O(M*N)             ~ 10^4 

*/


class Solution {
public:
    int getMaxRepetitions(string s1, int rep1, string s2, int rep2) {
        
        int n = s1.size();
        int m = s2.size();
        
        vector<vector<int>> nxt_ptr_txt(m, vector<int>(n)), nxt_ptr_pat(m, vector<int>(n));
        
        for (int i = 0; i < m; i++) {
            
            for (int j = 0; j < n; j++) {
                
                int cur_pat = i, cur_txt = j;
                
                while (cur_pat < m && cur_txt < n) {
                    if (s2[cur_pat] == s1[cur_txt]) cur_pat++;
                    cur_txt++;
                }
                
                nxt_ptr_txt[i][j] = cur_txt;
                nxt_ptr_pat[i][j] = cur_pat;
            }            
        }
        
        int found_pat = 0;
        int used_txt = 0;
        int cur_txt = 0, cur_pat = 0;
        
        while (used_txt < rep1) {
            
            int nxt_on_txt = nxt_ptr_txt[cur_pat][cur_txt];
            int nxt_on_pat = nxt_ptr_pat[cur_pat][cur_txt];
            
            cur_txt = nxt_on_txt;
            cur_pat = nxt_on_pat;
            
            if (cur_txt == n) {
                used_txt++;
                cur_txt = 0;
            } 
            
            if (cur_pat == m) {
                found_pat++;
                cur_pat = 0; 
            }
        }
        
        int max_reps = found_pat / rep2;
        
        return max_reps;
    }
    
};