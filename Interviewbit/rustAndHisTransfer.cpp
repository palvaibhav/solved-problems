/*
    https://www.hackerrank.com/contests/codeagon-2016/challenges/rust-transfer/problem
    Time:O(ElogV)
    Space:O(V)
*/

const int N=3e3+5,INF=1e9;
 
struct Node{
    int to,normal,taxi;
    Node(int a,int b,int c):to(a),normal(b),taxi(c){}
};
 
int n;
vector<Node> adj[N];
 
vector<int> djk(int s){
    vector<int> dis(n+1,INF);
    
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    
    dis[s]=0;
    pq.push({0,s});
    
    while(!pq.empty()){
        auto tmp=pq.top();
        pq.pop();
        int u=tmp.second;
        int nowDis=tmp.first;
        
        if(nowDis>dis[u])continue;
        
        for(Node& it:adj[u]){
            int v=it.to;
            int normal=it.normal;
            
            if(nowDis+normal<dis[v]){
                dis[v]=nowDis+normal;
                pq.push({dis[v],v});
            }
        }
    }
    
    return dis;
}
 
int Solution::solve(int A, vector<vector<int>> &e, int s, int d) {
    n=A;
    for(int i=1;i<=n;i++)adj[i].clear();
    
    int m=e.size();
    for(int i=0;i<m;i++){
        int u=e[i][0],v=e[i][1],normal=e[i][2],taxi=e[i][3];
        adj[u].push_back(Node(v,normal,taxi));
        adj[v].push_back(Node(u,normal,taxi));
    }
    
    vector<int> dis1=djk(s);
    vector<int> dis2=djk(d);
    
    int ans=dis1[d];
    
    for(int i=0;i<m;i++){
        int u=e[i][0],v=e[i][1],taxi=e[i][3];
        
        ans=min(ans,dis1[u]+dis2[v]+taxi);
        ans=min(ans,dis1[v]+dis2[u]+taxi);
    }
    
    return ans>=INF?-1:ans;
}