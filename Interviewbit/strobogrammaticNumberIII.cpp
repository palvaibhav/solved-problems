/*
    Time:O(5^8)
    Space:O(1)
*/


map<char,char> d={
    {'0','0'},
    {'1','1'},
    {'6','9'},
    {'8','8'},
    {'9','6'}
};

void gen(int pos,int len,string& cur,int& ans,long long l,long long r){
    if(pos==len){
        string str=cur;
        
        //even len
        for(int i=(int)cur.size()-1;i>=0;i--)str.push_back(d[cur[i]]);
        long long num=stoll(str);
        if(l<=num&&num<=r)ans++;
        
        if(cur.back()=='6'||cur.back()=='9')return;
        
        str=cur;
        //odd len
        for(int i=(int)cur.size()-2;i>=0;i--)str.push_back(d[cur[i]]);
        num=stoll(str);
        if(l<=num&&num<=r)ans++;
        
        return;
    }
    
    for(auto e:d){
        
        if(pos==0&&e.first=='0')continue;
        
        cur.push_back(e.first);
        gen(pos+1,len,cur,ans,l,r);
        cur.pop_back();
    }
}

int Solution::solve(string l, string r) {
    int nl=l.size(),nr=r.size();
    long long numl=stoll(l),numr=stoll(r);
    
    int ans=0;
    for(int len=1;len<=(nr+1)/2;len++){
        string cur;
        gen(0,len,cur,ans,numl,numr);
    }
    
    return ans;
}
