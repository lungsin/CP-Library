/**
 * Author: indy256
 * License: CC0
 * Source: https://sites.google.com/site/indy256/algo_cpp/dinic_flow
 * Description: Flow algorithm with guaranteed complexity $O(V^2 * E)$.
 * Status: Working
 * Usage:   addEdge(from, to, capacity)
 *          maxflow = maxFlow(_src, _dest) 
 */
 
#pragma once

const int maxnodes = 5000;

int nodes = maxnodes, src, dest;
int _dist[maxnodes], q[maxnodes], work[maxnodes];

struct Edge {
  int to, rev;
  int f, cap;
};

vector<Edge> g[maxnodes];

// Adds directional edge
void addEdge(int s, int t, int cap){
  Edge a = {t, (int) g[t].size(), 0, cap};
  Edge b = {s, (int) g[s].size(), 0, 0};
  g[s].push_back(a);
  g[t].push_back(b);
}

bool dinic_bfs() {
  fill(_dist, _dist + nodes, -1);
  _dist[src] = 0;
  int qt = 0;
  q[qt++] = src;
  for (int qh = 0; qh < qt; qh++) {
    int u = q[qh];
    for (int j = 0; j < (int) g[u].size(); j++) {
      Edge &e = g[u][j];
      int v = e.to;
      if (_dist[v] < 0 && e.f < e.cap) {
        _dist[v] = _dist[u] + 1;
        q[qt++] = v;
      }
    }
  }
  return _dist[dest] >= 0;
}

int dinic_dfs(int u, int f) {
  if (u == dest)
    return f;
  for (int &i = work[u]; i < (int) g[u].size(); i++) {
    Edge &e = g[u][i];
    if (e.cap <= e.f) continue;
    int v = e.to;
    if (_dist[v] == _dist[u] + 1) {
      int df = dinic_dfs(v, min(f, e.cap - e.f));
      if (df > 0) {
        e.f += df;
        g[v][e.rev].f -= df;
        return df;
      }
    }
  }
  return 0;
}

int maxFlow(int _src, int _dest) {
  src = _src;
  dest = _dest;
  int result = 0;
  while (dinic_bfs()) {
    fill(work, work + nodes, 0);
    while (int delta = dinic_dfs(src, INT_MAX))
      result += delta;
  }
  return result;
}

/**
int main() {
    int n = 3;
    nodes = n;

    int capacity[][3] = { { 0, 3, 2 }, { 0, 0, 2 }, { 0, 0, 0 } };
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (capacity[i][j] != 0)
                addEdge(i, j, capacity[i][j]);
    cout << (4 == maxFlow(0, 2)) << endl;
}
**/