#include<bits/stdc++.h>


#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define pf push_front
#define pb2 pop_back
#define pf2 pop_front
#define line printf("\n")
#define pq priority_queue
#define rep(k,i,j) for(int k = (int)i;k<(int)j;k++)
#define repd(k,i,j) for(int k = (int)i;k>=(int)j;k--)
#define ll long long
#define ALL(a) a.begin(),a.end()
#define vi vector<int>

using namespace std;

double EPS = 1e-9;
int INF = 1e9+7;;
long long INFLL = 1e17;
double pi = acos(-1);
int dirx[8] = {-1,0,0,1,-1,-1,1,1};
int diry[8] = {0,1,-1,0,-1,1,-1,1};

clock_t first_attempt = clock();
inline void cek_time(){
	clock_t cur = clock()- first_attempt;
	cerr<<"TIME : "<<(double) cur/CLOCKS_PER_SEC<<endl;
}
inline void OPEN (string s) {
	freopen ((s + ".in").c_str (), "r", stdin);
	freopen ((s + ".out").c_str (), "w", stdout);
}

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> bbst;

//end of template

const int maxn = 5e5+5;
int n;
int val[maxn];

int par[maxn][20],hi[maxn];

vi adj[maxn];

void dfs_lca(int a,int p){
    par[a][0] = p;
    hi[a] = hi[p] + 1;
    
    sz[a] = 1;
    for(auto b : adj[a]) if(b!=p){
        dfs_lca(b,a);
    }
}

int up(int a,int pts){
    repd(k,19,0)if((1<<k)<=pts){
        pts -= (1<<k);
        a = par[a][k];
    }
    return a;
}

int lca(int a,int b){
    if(hi[a]<hi[b])swap(a,b);
    int dis = abs(hi[a] - hi[b]);
    rep(k,0,20)if(dis&(1<<k))a = par[a][k];
    if(a==b)return a;
    repd(k,19,0)if(par[a][k]!=par[b][k]){
        a = par[a][k];
        b = par[b][k];
    }
    return par[a][0];
}

void setup_lca(){
    dfs_lca(1,0);
    rep(k,1,20)rep(i,1,n+1){
        int j = par[i][k-1];
        par[i][k] = par[j][k-1];
    }
}

