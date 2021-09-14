#pragma  GCC optimize ("Ofast")

#include <bits/stdc++.h>

#define endl      '\n'

using namespace std;

typedef long long  ll;

const int N = 1e9;

void Fast() {
    cin.sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}

bitset <N + 9> isComposite;

vector <int> coPrimes(int n)
{
    int basis [5] = {3, 5, 7, 11, 13};

    vector <int> ret;
    bitset <30100> isCoprime;
    isCoprime.set();

    for(int p : basis)
        for(int d = p * p; d <= n; d += p << 1)
            isCoprime.reset(d);

    for(int i = 15; i <= n; i += 2)
        if(isCoprime[i]) ret.push_back(i);

    ret.push_back(n + 1);
    ret.push_back(n + *ret.begin());

    return ret;
}

vector <int> wheel_sieve(int n)
{
    int basis [6] = {2, 3, 5, 7, 11, 13};
    vector <int> wheel = coPrimes(2*3*5*7*11*13);

    int sz = wheel.size();
    int inc [sz - 1];

    for(int i = 1; i < sz; ++i)
        inc[i - 1] = wheel[i] - wheel[i - 1];

    vector <int> ret;
    for(auto i : basis) if(i <= n)
            ret.push_back(i);

    int i = 0;
    for(int d = 17; d <= n; d += inc[i++]) {
        if(!isComposite[d]) {
            ret.push_back(d);
            for(ll j = (ll)d * d; j <= n; j += d + d) isComposite.set(j);
        }
        if(i == sz - 1) i = 0;
    }
    return ret;
}

int main()
{
    Fast();
    vector <int> Primes = wheel_sieve(100'000'000);

    for(int i = 0; i < Primes.size(); i += 100)
        cout << Primes[i] << "\n";
}
