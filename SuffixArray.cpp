// Source: http://codeforces.com/contest/452/submission/7269543
// Efficient Suffix Array O(N*logN)

// String index from 0
// Usage:
// string s;
// SuffixArray sa(s);
// Now we can use sa.SA and sa.LCP
struct SuffixArray{
    string a;
    int N, m;
    vector<int> SA, LCP, x, y, w, c;
    
    SuffixArray(string _a, int m = 1000) : a(" " + _a), N(a.length()), m(m),
            SA(N), LCP(N), x(N), y(N), w(max(m, N)), c(N) {
        a[0] = 0;
        DA();
        kasaiLCP();
        #define REF(X) { rotate(X.begin(), X.begin()+1, X.end()); X.pop_back(); }
        REF(SA); REF(LCP);
        a = a.substr(1, a.size());
        for(int i = 0; i < SA.size(); ++i) --SA[i];
        #undef REF
    }
    
    inline bool cmp (const int a, const int b, const int l) { return (y [a] == y [b] && y [a + l] == y [b + l]); }

    void Sort () {
        for (int i = 0; i < m; ++i) w [i] = 0;
        for (int i = 0; i < N; ++i) ++w [x [y [i]]];
        for (int i = 0; i < m - 1; ++i) w [i + 1] += w [i];
        for (int i = N - 1; i >= 0; --i) SA [--w [x [y [i]]]] = y [i];
    }

    void DA () {
        for (int i = 0; i < N; ++i) x [i] = a [i], y[i] = i;
        Sort();
        for (int i, j = 1, p = 1; p < N; j <<= 1, m = p) {
            for (p = 0, i = N - j; i < N; i++) y [p++] = i;
            for (int k = 0; k < N; ++k) if (SA [k] >= j) y [p++] = SA [k] - j;
            Sort ();
            for (swap (x, y), p = 1, x [SA [0]] = 0, i = 1; i < N; ++i) x [SA [i]] = cmp (SA [i - 1], SA [i], j) ? p - 1 : p++;
        }
    }

    void kasaiLCP () {
        for (int i = 0; i < N; i++) c [SA [i]] = i;
        for (int i = 0, j, k = 0; i < N; LCP [c [i++]] = k)
            if (c [i] > 0) for (k ? k-- : 0, j = SA [c [i] - 1]; a [i + k] == a [j + k]; k++);
            else k = 0;
    }
};


const int maxn = 1e5 +5;
struct perfectHash{
    int sparse[maxn][20];
    int rev[maxn];

    ll f(int l, int r){
        int la = rev[l];
        int len = r - l + 1;
        
        repd(i,19,0){
            if(sparse[la][i] >= len){
                la -= (1<<i);
            }
        }
        return (ll) la*maxn + len;
    }
    
    int LCP(int l,int r) {
        int a = rev[l], b = rev[r];
        if (a > b) swap(a, b);
        int ret = INF;
        repd(i,19,0) {
            if (b - (1<<i) >= a){
                ret = min(ret, sparse[b][i]);
                b -= (1<<i);
            }
        }
        return ret;
    }
    
    void init(string &s){
        SuffixArray ss (s, 300);
        rep(k,0,s.size())
            rev[ss.SA[k]] = k;
        
        rep(k,0,s.size())
            sparse[k][0] = ss.LCP[k];
            
        rep(i,1,20)rep(k,0,s.size()){
            int kk = max(0, k - (1<<(i-1)));
            sparse[k][i] = min(sparse[k][i-1], sparse[kk][i-1]);
        }
    }
} GG;