#pragma  GCC optimize ("Ofast")

#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef __int128_t i128;
typedef __uint128_t ui128;
typedef long double ld;

void Fast() {
    istream::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

const int N = 1e6 + 9, M = N << 1, oo = 0x3f3f3f3f, Mod = 1e9 + 7;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ld eps = 1e-9;

ull rel[N];

void preprocessing() {
    for (int i = 1; i < N; ++i)
        rel[i] = i;

    for (int i = 2; i < N; ++i)
        if (rel[i] == i) {
            for (int j = i; j < N; j += i)
                rel[j] -= rel[j] / i;
        }
}

int n;

void Solve() {
    cin >> n;
    cout << rel[n] << endl;
}

int main() {
    Fast();
    preprocessing();

    int tc = 1;
    cin >> tc;
    for (int i = 1; i <= tc; ++i) {
        Solve();
    }
}
