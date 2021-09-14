/**
	constraints:
	1 <= l, r <= 1e{14}
	1 <= r - l + 1 <= 1e7
	Time complexity of this approach is : O((r â�� l + 1)lnln(r) + â��r lnln r^{1/4})
**/

#pragma  GCC optimize ("Ofast")

#include <bits/stdc++.h>

#define endl      '\n'

using namespace std;

typedef long long  ll;
typedef __int128 i128;

const int N = 1e6;
int cnt;

void Fast() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

vector <int> Primes;
bitset <N + 9> isPrime;

void sieve(ll n) {
    isPrime.set();
    int _sqrt = sqrtl(n);

    for(int i = 5; i <= _sqrt; i += 6) {
        if(isPrime[i])
            for (int j = i * i; j <= n; j += i + i) isPrime.reset(j);
        i += 2;
        if(isPrime[i])
            for (int j = i * i; j <= n; j += i + i) isPrime.reset(j);
        i -= 2;
    }

    if(n >= 2) Primes.push_back(2);
    if(n >= 3) Primes.push_back(3);

    for(int i = 5; i <= n; i += 6) {
        if(isPrime[i])
            Primes.push_back(i);
        i += 2;
        if(i > n) break;
        if(isPrime[i])
            Primes.push_back(i);
        i -= 2;
    }
}

void segmented_sieve(ll l, ll r) {
    l += l == 1;
    int _range = r - l + 1;
    isPrime.set();

    for(int i = 0; i < (int)Primes.size() && (ll)Primes[i] * Primes[i] <= r; ++i) {
        ll st = (l / Primes[i]) * Primes[i];
        st += (st < l ? Primes[i] : 0);

        for(ll j = st; j <= r; j += Primes[i]) if(j != Primes[i])
                isPrime.reset(j - l);
    }

    for(int i = 0; i < _range; ++i)
        if(isPrime[i]) {
            ++cnt;
            if(cnt % 500 == 1)
                cout << i + l << '\n';
        }
}


ll binpower(ll base, ll e, ll mod) {
    ll result = 1;
    base %= mod;
    while (e) {
        if (e & 1ll)
            result = (i128)result * base % mod;
        base = (i128)base * base % mod;
        e >>= 1ll;
    }
    return result;
}

bool check_composite(ll n, ll a, ll d, int s) {
    ll x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (i128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(ll n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    ll d = n - 1;
    while ((d & 1ll) == 0) {
        d >>= 1ll;
        ++r;
    }

    for (int a : {
                2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37
            }) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

int main() {
    Fast();
    int tc;
    cin >> tc;
    ll n;
    for(int i = 1; i <= tc; ++i) {
        cin >> n;
        if(MillerRabin(n))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;

    sieve(N);

    for(int i = 0; i < Primes.size(); ++i)
        if((i + 1) % 500 == 1)
            cout << Primes[i] << '\n';

    cnt = Primes.size();
    for(int i = N; i <= 1e9 - N; i += N) {
        segmented_sieve(i, i + N);
    }
}
