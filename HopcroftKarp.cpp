// Maximum matching for bipartite graph. Hopcroft-Karp algorithm in O(E * sqrt(V))

#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN1 = 50000;
const int MAXN2 = 50000;
const int MAXM = 150000;

int n1, n2, edges, last[MAXN1], Prev[MAXM], Head[MAXM];
int matching[MAXN2], dist[MAXN1], Q[MAXN1];
bool used[MAXN1], vis[MAXN1];

void init(int _n1, int _n2) {
    n1 = _n1;
    n2 = _n2;
    edges = 0;
    fill(last, last + n1, -1);
}

void addEdge(int u, int v) {
    Head[edges] = v;
    Prev[edges] = last[u];
    last[u] = edges++;
}

void bfs() {
    fill(dist, dist + n1, -1);
    int sizeQ = 0;
    for (int u = 0; u < n1; ++u) {
        if (!used[u]) {
            Q[sizeQ++] = u;
            dist[u] = 0;
        }
    }
    for (int i = 0; i < sizeQ; i++) {
        int u1 = Q[i];
        for (int e = last[u1]; e >= 0; e = Prev[e]) {
            int u2 = matching[Head[e]];
            if (u2 >= 0 && dist[u2] < 0) {
                dist[u2] = dist[u1] + 1;
                Q[sizeQ++] = u2;
            }
        }
    }
}

bool dfs(int u1) {
    vis[u1] = true;
    for (int e = last[u1]; e >= 0; e = Prev[e]) {
        int v = Head[e];
        int u2 = matching[v];
        if (u2 < 0 || !vis[u2] && dist[u2] == dist[u1] + 1 && dfs(u2)) {
            matching[v] = u1;
            used[u1] = true;
            return true;
        }
    }
    return false;
}

int maxMatching() {
    fill(used, used + n1, false);
    fill(matching, matching + n2, -1);
    for (int res = 0;;) {
        bfs();
        fill(vis, vis + n1, false);
        int f = 0;
        for (int u = 0; u < n1; ++u)
            if (!used[u] && dfs(u))
                ++f;
        if (!f)
            return res;
        res += f;
    }
}

int flagL[MAXN1], flagR[MAXN2];
void dfs_mvc(int a) {
    if (a < 0 || flagL[a]) return;
    flagL[a] = 1;
    
    for (int e = last[a]; e >= 0; e = Prev[e]) {
        int b = Head[e];
        flagR[b] = 1;
        int mb = matching[b];
        dfs_mvc(mb);
    }
}

int get_mvc(vi &L, vi &R) {
    int max_matching = maxMatching();
    fill(flagL, flagL + n1, 1);
    vector<int> st;
    for (int k = 0; k < n2; k++) if (matching[k] != -1) flagL[matching[k]] = 0;
    for (int k = 0; k < n1; k++) if (flagL[k]) st.pb(k);
    fill(flagL, flagL + n1, 0);
    fill(flagR, flagR + n2, 0);
    for (auto a : st) dfs_mvc(a);
    for (int k = 0; k < n1; k++) if (flagL[k] == 0) L.pb(k);
    for (int k = 0; k < n2; k++) if (flagR[k] == 1) R.pb(k);
    
    return max_matching;
}

int main() {
    init(2, 2);

    addEdge(0, 0);
    addEdge(0, 1);
    addEdge(1, 1);

    cout << (2 == maxMatching()) << endl;
}
