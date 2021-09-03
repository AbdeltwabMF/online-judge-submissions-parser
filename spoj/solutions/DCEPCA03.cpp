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

int mu[N], lp[N], Primes[78522], pnx;

void mu_sieve(int n) {
    mu[1] = 1;
    fill(mu, mu + N, 1);
    for (int i = 2; i <= n; ++i) {
        if (lp[i] == 0) {
            lp[i] = Primes[pnx++] = i;
            mu[i] = -1;
        }
        for (int j = 0, nxt; j < pnx && Primes[j] <= lp[i] && (nxt = i * Primes[j]) <= n; ++j) {
            lp[nxt] = Primes[j];
            mu[nxt] = (lp[i] == Primes[j] ? 0 : -mu[i]);
        }
    }
}

int phi[10010], pref[10010];

void phi_sieve(int n) {
    for (int i = 1; i <= n; ++i) phi[i] = i;

    for (int i = 2; i <= n; ++i) {
        if (phi[i] == i)
            for (int j = i; j <= n; j += i) {
                phi[j] -= phi[j] / i;
            }
    }

    for (int i = 1; i <= n; ++i) {
        pref[i] += pref[i - 1] + phi[i];
    }
}

ll binExp(ll a, ll b) {
    ull res = 1;
    for (; b; b >>= 1) {
        if (b & 1ll)
            res = res * a;
        a = a * a;
    }
    return res;
}

int divisors[N];

void factorization(int a) { // log a
    int n = a;
    while (n > 1) {
        int p = lp[n], cnt = 0;
        while (n % p == 0) n /= p, ++cnt;
        divisors[a] *= (binExp(p, cnt + 1) - 1) / (p - 1);
    }
}

int n;
const int d = 2;

void Solve() {
    cin >> n;

    ll ans = 0;
    for (int j = 1, i = phi[j]; j <= n; i = phi[++j]) {
        ans += i *1ll* pref[j] + i *1ll* pref[j - 1];
    }
    cout << ans << endl;
}

int main() {
    Fast();
    phi_sieve(10000);

    int tc = 1;
    cin >> tc;
    for (int i = 1; i <= tc; ++i) {
        Solve();
    }
}
