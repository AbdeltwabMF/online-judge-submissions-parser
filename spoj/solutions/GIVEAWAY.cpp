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
}

const int N = 5e5 + 9, M = 2e3 + 9, oo = 0x3f3f3f3f, Mod = 1e9 + 7;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int BLK = 256;

int n, q, a[N], type, x, y, z;
vector <int> bs[M];

int query(int l, int r, int val)
{
    int cur_l = l / BLK;
    int cur_r = r / BLK;
    int ans = 0;

    if(cur_l == cur_r) {
        for (int i = l; i <= r; ++i)
            ans += (a[i] >= val);
    } else {
        for(int i = l, _end = (cur_l + 1) * BLK; i < _end; ++i)
            ans += (a[i] >= val);
        for(int i = cur_l + 1; i <= cur_r - 1; ++i)
            ans += bs[i].end()-  lower_bound(bs[i].begin(), bs[i].end(), val);
        for(int i = cur_r * BLK; i <= r; ++i)
            ans += (a[i] >= val);
    }
    return ans;
}

void build() {
    int numberOfBLKs = ceil((double)n / BLK);
    for(int i = 0; i < n; ++i)
        bs[i / BLK].emplace_back(a[i]);

    for(int i = 0; i < numberOfBLKs; ++i)
        sort(bs[i].begin(), bs[i].end());
}

void update(int id, int delta)
{
    int pos = lower_bound(bs[id / BLK].begin(), bs[id / BLK].end(), a[id]) - bs[id / BLK].begin();
    bs[id / BLK][pos] = delta;
    sort(bs[id / BLK].begin(), bs[id / BLK].end());
    a[id] = delta;
}

void Solve()
{
    cin >> n;
    for(int i = 0; i < n; ++i) cin >> a[i];

    BLK = sqrtl(n + .0) + 1;
    build();

    cin >> q;
    while(q--)
    {
        cin >> type >> x >> y;x--;
        if(type == 0)
        {
            cin >> z;y--;
            cout << query(x, y, z) << endl;
        }
        else
            update(x, y);
    }
}

int main()
{
    Fast();

    int tc = 1;
    for(int i = 1; i <= tc; ++i)
        Solve();
}
