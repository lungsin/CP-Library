// 2009 Shanghai: Heroes Arrangement
// ACM-ICPC Live Archive 4750

#define N 50

int g[N][N], n;

// MaxClique
int dp[N], best;
int dfs(int n, int* u, int size) {
  int i, j, vn, v[N];
  if (n) {
    if (size + dp[u[0]] <= best)
      return 0;
    for (i = 0; i < n + size - best && i < n; i++) {
      for (j = i + 1, vn = 0; j < n; ++j)
        if (g[u[i]][u[j]])
          v[vn++] = u[j];
      if (dfs(vn, v, size + 1))
        return 1;
    }
  } else if (size > best) {
    best = size;
    return 1;
  }
  return 0;
}

int maxclique() {
  int i, j, vn, v[N];
  best = 0;
  for (dp[i = n - 1] = 0; i >= 0; --i) {
    for (vn = 0, j = i + 1; j < n; ++j)
      if (g[i][j])
        v[vn++] = j;
    dfs(vn, v, 1);
    dp[i] = best;
  }
  return best;
}

// End of MaxClique
