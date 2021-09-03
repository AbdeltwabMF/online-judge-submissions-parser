#pragma GCC optimize ("Ofast")

#include <bits/stdc++.h>

#define endl        '\n'

using namespace std;

typedef int64_t    ll;
typedef __int128 i128;

void Fast() {
    cin.sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}

void File() {
    freopen("input.in",  "r", stdin);
    freopen("output.out", "w", stdout);
}

const int N = 3e4 + 9, M = 2e5 + 9, oo = 0x3f3f3f3f, Mod = 1e9 + 7;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int BLK = 256;

struct query
{
    int l, r, id, blk;

    query() = default;
    query(int _l, int _r, int _id)
    {
        l = _l;
        r = _r;
        id = _id;
        blk = l / BLK;
    }

    bool operator < (const query other) const {
        if(blk ^ other.blk)
            return blk < other.blk;
        return (blk & 1) ? r < other.r : r > other.r;
    }
} queries[M];

int res[M], freq[M << 3], cur;

void add(int id) {
    cur += (++freq[id] == 1);
}

void remove(int id) {
    cur -= (--freq[id] == 0);
}

void process(int id, int delta) {
    if(delta > 0) add(id);
    else remove(id);
}

int cur_l, cur_r, l, r, n, q, a[N];

void Solve()
{
    cin >> n; a[0] = 0;
    for(int i = 1; i <= n; ++i) cin >> a[i];

    cin >> q;
    for(int i = 1; i <= q; ++i)
    {
        cin >> l >> r;
        queries[i] = query(l, r, i);
    }

    sort(queries + 1, queries + 1 + q);
//    for(int i = 1; i <= q; ++i)
//        cout << queries[i].l << " " << queries[i].r << " " << queries[i].blk << endl;

    cur_l = 0, cur_r = 0;
    for(int i = 1; i <= q; ++i)
    {
        int ql = queries[i].l;
        int qr = queries[i].r;

        // Add right
        while(cur_r < qr) process(a[++cur_r], 1);
        // Add left
        while(cur_l > ql) process(a[--cur_l], 1);
        // Remove right
        while(cur_r > qr) process(a[cur_r--], -1);
        // Remove left
        while(cur_l < ql) process(a[cur_l++], -1);

        res[queries[i].id] = cur;
    }

    for(int i = 1; i <= q; ++i)
        cout << res[i] << "\n";
}

int main()
{
    Fast();

    int tc = 1;
    for(int i = 1; i <= tc; ++i)
        Solve();
}
