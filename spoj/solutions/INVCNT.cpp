#pragma GCC optimize ("Ofast")

#include <bits/stdc++.h>

#define endl        '\n'
#define Min(a, b)   (((a) < (b)) ? (a) : (b))
#define Max(a, b)   (((a) > (b)) ? (a) : (b))

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

const int N = 1e6 + 9, M = 2e6 + 9, oo = 0x3f3f3f3f;
ll INF = 0x3f3f3f3f3f3f3f3f;

ll inversions;

template <class T>
void merge(T localArr [], int l, int mid, int r)
{
    int l_size = mid - l + 1;
    int r_size = r - mid;

    T L[l_size + 1];
    T R[r_size + 1];

    for(int i = 0; i < l_size; ++i) L[i] = localArr[i + l];
    for(int i = 0; i < r_size; ++i) R[i] = localArr[i + mid + 1];

    T Mx;
    if(sizeof(T) == 4) Mx = INT_MAX;
    else Mx = LONG_MAX;

    L[l_size] = R[r_size] = Mx;

    for(int k = l, i = 0, j = 0; k <= r; ++k)
        if(L[i] <= R[j])
            localArr[k] = L[i], i += (L[i] != Mx);
        else
            localArr[k] = R[j], j += (R[j] != Mx), inversions += l_size - i;
}

template <class T>
void merge_sort(T localArr [], int l, int r)
{
    if(r - l)
    {
        int mid = (l + r) >> 1;
        merge_sort(localArr, l,     mid);
        merge_sort(localArr, mid + 1, r);
        merge(localArr,      l,  mid, r);
    }
}

template <class T>
void merge_sort(T _begin, T _end)
{
    const int sz = _end - _begin;
    __typeof(*_begin) localArray[sz];

    __typeof(_begin) k = _begin;
    for(int i = 0; k != _end; ++i, ++k)
        localArray[i] = *k;

    merge_sort(localArray, 0, sz - 1);

    k = _begin;
    for(int i = 0; k != _end; ++i, ++k)
        *k = localArray[i];
}

ll n, a[N];

void Solve()
{
    cin >> n;
    for(int i = 0; i < n; ++i) cin >> a[i];

    inversions = 0;
    merge_sort(a, a + n);

    cout << inversions << endl;
}

int main()
{
    Fast();

    int tc = 1; cin >> tc;
    for(int i = 1; i <= tc; ++i)
        Solve();
}
