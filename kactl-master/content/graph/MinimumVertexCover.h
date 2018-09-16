/**
 * Author: Lung Sin
 * Date: 2016-12-15
 * License: CC0
 * Description: Finds a minimum vertex cover in a bipartite graph.
 *  The size is the same as the size of a maximum matching, and
 *  the complement is an independent set.
 * Status: fuzz-tested
 */
#pragma once

#include "hopcroftKarp.h"

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

// L and R are the vertex covered
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
