#pragma GCC optimize ("Ofast")

#include <bits/stdc++.h>

#define endl        '\n'
#define Min(a, b)   (((a) < (b)) ? (a) : (b))
#define Max(a, b)   (((a) > (b)) ? (a) : (b))

using namespace std;

typedef int64_t  ll;

void Fast() {
    cin.sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}

void File() {
    freopen("input.in",  "r", stdin);
    freopen("output.out", "w", stdout);
}

const int N = 1e5 + 9, M = 2e6 + 9, oo = 0x3f3f3f3f;
ll INF = 0x3f3f3f3f3f3f3f3f;

class UnionFind
{
    vector <int> par;
    vector <int> siz;
    int num_sets;
    size_t sz;

  public:
    UnionFind(int n) : par(n + 1, -1), siz(n + 1, 1), num_sets(n), sz(n) {}

    int find_set(int u)
    {
        assert(u <= sz);

        int leader;
        for(leader = u; ~par[leader]; leader = par[leader]);

        for(int next = par[u]; u != leader; next = par[next]) {
            par[u] = leader;
            u = next;
        }
        return leader;
    }

    bool same_set(int u, int v) {
        return find_set(u) == find_set(v);
    }

    bool union_set(int u, int v) {
        if(same_set(u, v)) return false;

        int x = find_set(u);
        int y = find_set(v);

        if(siz[x] < siz[y]) swap(x, y);

        par[y] = x;
        siz[x] += siz[y];

        --num_sets;
        return true;
    }

    int number_of_sets() {
        return num_sets;
    }

    int size_of_set(int u) {
        return siz[find_set(u)];
    }

    size_t size() {
        return sz;
    }

    void clear() {
        par.clear();
        siz.clear();
        sz = num_sets = 0;
    }

    void assign(size_t n) {
        par.assign(n + 1, -1);
        siz.assign(n + 1,  1);
        sz = num_sets = n;
    }

    map < int, vector <int> > groups(int st) {
        map < int, vector <int> > ret;

        for(size_t i = st; i < sz + st; ++i)
            ret[find_set(i)].push_back(i);

        return ret;
    }
};

int n, m ,u, v, tax;
vector < tuple <int, int, int> > edges;

pair < ll, vector < pair <int, int> > > Kruskal(int n)
{
    UnionFind uf(n);
    sort(edges.begin(), edges.end());

    vector < pair <int, int> > mstEdges(n - 1);
    int from, to, cost, inx = 0;
    ll minWieght = 0;

    for(tuple <int, int, int> edge : edges)
    {
        tie(cost, from, to) = edge;
        if(uf.union_set(from, to))
        {
            minWieght += cost;
            mstEdges[inx++] = make_pair(from, to);
        }
    }

    if(inx == n - 1)
        return make_pair(minWieght, mstEdges);

    return make_pair(-1, vector < pair <int, int> > ());
}

void Solve()
{
    cin >> n >> m;

    while(m--) {
        cin >> u >> v >> tax;
        edges.push_back({tax, u, v});
    }

    vector < pair <int, int> > MST;
    ll minWieght = 0;

    tie(minWieght, MST) = Kruskal(n);

    cout << minWieght << endl;
}

int main()
{
    Fast();

    int tc = 1;
    for(int i = 1; i <= tc; ++i)
        Solve();
}
