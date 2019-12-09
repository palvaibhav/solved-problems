
/*
    Soltion 1
    
    Time : O(K * N^3)
    Space : O(K * N^2)

*/
class Solution {
public:
    
    struct Data {
        bool found = false;
        vector<int> mx;
    };
    
    bool compare(vector<int>& A, vector<int>& B) {
        int n = A.size(), m = B.size();
        int i = 0, j = 0;
        
        // while (i < n && A[i] == 0) i++;
        // while (j < m && B[j] == 0) j++;
        
        int len1 = n - i;
        int len2 = m - j;
        
        if (len1 > len2) return true;
        else if (len1 < len2) return false;
        else {
            while (i < n && j < m) {
                if (A[i] > B[j]) return true;
                else if (A[i] < B[j]) return false;
                i++, j++;
            }
            return true;
        }
    }
    
    int n, m;
    vector<int> A, B;
    vector<vector<vector<Data>>> dp;
    
    Data go(int i, int j, int k) {
        if (k == 0) return Data();
        
        if (i >= n && j >= m) return Data();
        
        Data& ans = dp[i][j][k];
        
        if (ans.found) return ans;
        
        if (i >= n) {
            
            vector<int> small_ans = go(i, j + 1, k - 1).mx;
            
            vector<int> option = {B[j]};
            option.insert(option.end(), small_ans.begin(), small_ans.end());
            
            if (compare(option, ans.mx)) ans.mx = option;
            
            small_ans = go(i, j + 1, k).mx;
        
            if (compare(small_ans, ans.mx)) ans.mx = small_ans;
            
            ans.found = true;
            
            return ans;
        }
        
        if (j >= m) {
            
            vector<int> small_ans = go(i + 1, j, k - 1).mx;
            
            vector<int> option = {A[i]};
            option.insert(option.end(), small_ans.begin(), small_ans.end());
            
            if (compare(option, ans.mx)) ans.mx = option;
            
            small_ans = go(i + 1, j, k).mx;
        
            if (compare(small_ans, ans.mx)) ans.mx = small_ans;
            
            ans.found = true;
            
            return ans;
        }           
        
        
        // placing a digit
        if (i < n) {
            vector<int> small_ans = go(i + 1, j, k - 1).mx;
            
            vector<int> option = {A[i]};
            option.insert(option.end(), small_ans.begin(), small_ans.end());
            
            if (compare(option, ans.mx)) ans.mx = option;
        }
        if (j < m) {
            vector<int> small_ans = go(i, j + 1, k - 1).mx;
            
            vector<int> option = {B[j]};
            option.insert(option.end(), small_ans.begin(), small_ans.end());
            
            if (compare(option, ans.mx)) ans.mx = option;
        }
        
        // ignoring digits
        vector<int> small_ans = go(i + 1, j, k).mx;
        
        if (compare(small_ans, ans.mx)) ans.mx = small_ans;
        
        small_ans = go(i, j + 1, k).mx;
        
        if (compare(small_ans, ans.mx)) ans.mx = small_ans;
        
        ans.found = true;
        
        return ans;
    }
    
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        A = nums1, B = nums2;
        n = A.size(), m = B.size();
        
        dp = vector<vector<vector<Data>>>(n + 5, vector<vector<Data>>(m + 5, vector<Data>(k + 5)));
        
        return go(0, 0, k).mx;        
    }
};

//--------------------------------------------------------------------------------------------------------


/*
    Solution 2:
    
    Time : O(N^3)
    Space : O(N) 

*/

class Solution {
public:
    
    // O(N + M) ~ O(N)
    bool bigger(vector<int>& nums1, int idx1, vector<int>& nums2, int idx2) {
        int n = nums1.size(), m = nums2.size();
        
        while (idx1 < n && idx2 < m) {
            if (nums1[idx1] > nums2[idx2]) return true;
            else if (nums1[idx1] < nums2[idx2]) return false;
            
            idx1++, idx2++;
        }
        
        return idx1 < n;
    }
    
    // O(N * K) ~ O(N^2)
    vector<int> maxNumberOfLenK(vector<int>& nums, int k) {
        
        int n = nums.size();
        
        if (k == 0) return {};
        
        vector<int> res(k);
        
        int idx = 0, ptr = 0;
        
        while (idx < n) {
            
            while (ptr >= 0 && nums[idx] > res[ptr] && n - idx >= k - ptr) ptr--;
            
            if (ptr + 1 < k) res[++ptr] = nums[idx];
            
            idx++;
        }
        
        return res;
    }
    
    // O((N + M)^2) ~ O(N^2)
    vector<int> merge(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        int idx1 = 0, idx2 = 0;
        
        vector<int> res;
        
        while (idx1 < n && idx2 < m) {
            if (bigger(nums1, idx1, nums2, idx2)) res.push_back(nums1[idx1++]);
            else res.push_back(nums2[idx2++]);
        }
        
        while (idx1 < n) res.push_back(nums1[idx1++]);
        
        while (idx2 < m) res.push_back(nums2[idx2++]);
        
        return res;
    }
    
    // O(N * ((N * K) + (N + M)^2)) ~ O(N^3)
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        
        int n = nums1.size(), m = nums2.size();
        
        vector<int> ans;
        
        for (int cnt1 = 0; cnt1 <= min(n, k); cnt1++) {
            int cnt2 = k - cnt1;
            if (m >= cnt2 && cnt2 >= 0) {
                vector<int> part1 = maxNumberOfLenK(nums1, cnt1);
                vector<int> part2 = maxNumberOfLenK(nums2, cnt2);
                vector<int> candidate = merge(part1, part2);
                if (bigger(candidate, 0, ans, 0)) ans = candidate;
            }
        }
        
        return ans;
    }
};