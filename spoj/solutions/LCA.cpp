#pragma GCC optimize ("Ofast")

#include <bits/stdc++.h>

using namespace std;

typedef int64_t    ll;

void Fast() {
    cin.sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}

const int N = 1e5 + 9, M = 2e5 + 9, oo = 0x3f3f3f3f, Mod = 1e9 + 7;
const int LOG = 20;

int Head[N], To[M], Next[M], Par[N];
int ne, n, u, v, q, d;
int up[N][LOG + 1];
int Log[N];
int dfs_in[N], dfs_out[N], dfs_timer;

void addEdge(int from, int to) {
    Next[++ne] = Head[from];
    Head[from] = ne;
    To[ne] = to;
}

void _clear() {
    memset(Head,  0, sizeof(Head[0])   * (n + 2));
    memset(Par,   0, sizeof(Par[0])    * (n + 2));
    ne = dfs_timer = 0;
}

int lastBit(int a) {
    return (a & -a);
}

void logCalc() {
    Log[1] = 0;
    for(int i = 2; i < N; ++i)
        Log[i] = Log[i >> 1] + 1;
}

void DFS(int node)
{
    dfs_in[node] = ++dfs_timer;
    up[node][0] = Par[node];

    for(int i = 1; i <= LOG; ++i) {
        up[node][i] = up[up[node][i - 1]][i - 1];
    }

    for(int i = Head[node]; i; i = Next[i]) if(To[i] != Par[node]) {
            Par[To[i]] = node;
            DFS(To[i]);
        }

    dfs_out[node] = ++dfs_timer;
}

bool isAncestor(int u, int v) {
    return dfs_in[u] <= dfs_in[v] && dfs_out[u] >= dfs_out[v];
}

int LCA(int u, int v)
{
    if(isAncestor(u, v)) return u;
    if(isAncestor(v, u)) return v;

    for(int i = LOG; i >= 0; --i)
        if(!isAncestor(up[u][i], v))
            u = up[u][i];

    return up[u][0];
}

void Solve()
{
    cin >> n;
    _clear();

    for(int i = 1; i <= n; ++i) {
        int m; cin >> m;
        for(int j = 1; j <= m; ++j)
        {
            cin >> v;
            addEdge(i, v);
            addEdge(v, i);
        }
    }

    logCalc();
    for(int i = 1; i <= n; ++i) if(Par[i] == 0)
    {
        Par[i] = i;
        DFS(i);
    }

    cin >> q;
    while(q--)
    {
        cin >> u >> v;
        cout << LCA(u, v) << "\n";
    }
}

int main()
{
    Fast();

    int tc = 1; cin >> tc;
    for(int i = 1; i <= tc; ++i)
    {
        cout << "Case " << i << ":\n";
        Solve();
    }
}
