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

ll gcd(ll a, ll b) {
    if (!a)
        return b;

    int shift = __builtin_ctz(a | b);
    a >>= __builtin_ctz(a);

    while (b) {
        b >>= __builtin_ctz(b);
        if (a > b)
            swap(a, b);
        b -= a;
    }
    return a << shift;
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

/*int lp[N];
int Primes[664580], pnx; *//** size of Primes = n / (ln(n) - 1.08) *//*

void linear_sieve(int n) {
    for (int i = 2; i <= n; ++i) {
        if (lp[i] == 0) {
            lp[i] = Primes[pnx++] = i;
        }
        for (int j = 0, comp; j < pnx && Primes[j] <= lp[i] && (comp = i * Primes[j]) <= n; ++j) {
            lp[comp] = Primes[j];
        }
    }
}*/

int EulerPhi[N];

void Phi_sieve(int n) {
    for (int i = 1; i <= n; ++i) EulerPhi[i] = i;
    for (int i = 2; i <= n; ++i) {
        if (EulerPhi[i] == i)
            for (int j = i; j <= n; j += i) {
                EulerPhi[j] -= EulerPhi[j] / i;
            }
    }
    ++EulerPhi[1];
}

ll Divisors[N];

void Divisors_sieve(int x) {
    for (int i = 1; i <= x; ++i) {
        for (int j = i; j <= x; j += i) {
            Divisors[j] += i *1ll* EulerPhi[i];
        }
    }
}

/*
vector<pair<int, int>> Factorization(int n) {
    vector<pair<int, int>> ret;
    while (n > 1) {
        int p = lp[n], cnt = 0;
        while (n % p == 0) n /= p, ++cnt;
        ret.emplace_back(p, cnt);
    }
    return ret;
}*/

int n;

void Solve() {
    cin >> n;
    cout << Divisors[n] * n / 2 << endl;
}

int main() {
    Fast();
    Phi_sieve(1'000'000);
    Divisors_sieve(1'000'000);

    int tc = 1;
    cin >> tc;
    for (int i = 1; i <= tc; ++i) {
        Solve();
    }
}
