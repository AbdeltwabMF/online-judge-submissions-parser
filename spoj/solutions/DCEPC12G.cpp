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

const int N = 1e7 + 9, M = N << 1, oo = 0x3f3f3f3f, Mod = 1e9 + 7;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ld eps = 1e-9;

int lp[N], Primes[664999], pnx;
ll pref[N];
// mu[N],

void mu_sieve(int n) {
    //mu[1] = 1;
    //fill(mu, mu + N, 1);
    for (int i = 2; i <= n; ++i) {
        if (lp[i] == 0) {
            lp[i] = Primes[pnx++] = i;
            //mu[i] = -1;
        }
        for (int j = 0, nxt; j < pnx && Primes[j] <= lp[i] && (nxt = i * Primes[j]) <= n; ++j) {
            lp[nxt] = Primes[j];
            //mu[nxt] = (lp[i] == Primes[j] ? 0 : -mu[i]);
        }
    }
}

int phi[N];

void phi_sieve(int n) {
    for (int i = 1; i <= n; ++i) phi[i] = i;

    for (int i = 2; i <= n; ++i) {
        if (phi[i] == i)
            for (int j = i; j <= n; j += i) {
                phi[j] -= phi[j] / i;
            }
    }
}

ll binExp(ll a, ll b, ll p) {
    ull res = 1;
    for (; b; b >>= 1) {
        if (b & 1ll)
            res = res * a % p;
        a = a * a % p;
    }
    return res;
}

/*
int divisors[N];

void factorization(int a) { // log a
    int n = a;
    while (n > 1) {
        int p = lp[n], cnt = 0;
        while (n % p == 0) n /= p, ++cnt;
        divisors[a] *= (binExp(p, cnt + 1) - 1) / (p - 1);
    }
}
*/

ll n, fact[664999];
const int d = 2;

void Solve() {
    cin >> n;
    int inx = pref[n] - phi[n];
    if(inx < 0) inx = 0;

    cout << binExp(phi[n], fact[inx], Mod) << endl;
}

int main() {
    Fast();
    mu_sieve(10000000);
    phi_sieve(10000000);

    fact[0] = 1;
    for (int i = 1; i <= 664999; ++i) {
        fact[i] = fact[i - 1] * i % (Mod - 1);
    }

    for (int i = 0; i < pnx; ++i) {
        pref[Primes[i]] = 1;
    }

    for (int i = 1; i <= 10000000; ++i) {
        pref[i] += pref[i - 1];
    }

    int tc = 1;
    cin >> tc;
    for (int i = 1; i <= tc; ++i) {
        Solve();
    }
}
