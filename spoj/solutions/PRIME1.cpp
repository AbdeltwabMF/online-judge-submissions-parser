#pragma  GCC optimize ("Ofast")

#include <bits/stdc++.h>

#define  endl    '\n'

using namespace std;

typedef long long ll;

void Fast() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

/// Set your CPU's L1 data cache size (in bytes) here
const int64_t L1D_CACHE_SIZE = 32768;
//const int64_t N = 32768;
/// Generate primes using the segmented sieve of Eratosthenes.
/// This algorithm uses O(n log log n) operations and O(sqrt(n)) space.
/// @param limit  Sieve primes <= limit.
vector <ll> prim;

void segmented_sieve(int64_t limit) {
    int64_t sqrt = sqrtl(limit);
    int64_t segment_size = max(sqrt, L1D_CACHE_SIZE);
    int64_t count = 1;
//    cout<<2<<endl;
    prim.push_back(2);
    // we sieve primes >= 3
    int64_t i = 3;
    int64_t n = 3;
    int64_t s = 3;

//    vector<char> sieve(segment_size);
//    vector<char> is_prime(sqrt + 1, true);
//    bitset <L1D_CACHE_SIZE> sieve, is_prime;
//    is_prime.set();
    bool sieve[segment_size];
    bool is_prime[sqrt+1];
    fill(is_prime, is_prime+sqrt+1, true);
    vector<int64_t> primes;
    vector<int64_t> multiples;

    for (int64_t low = 0; low <= limit; low += segment_size) {
        //fill(sieve.begin(), sieve.end(), true);
//        sieve.set();
        fill(sieve, sieve+segment_size, true);
        // current segment = [low, high]
        int64_t high = low + segment_size - 1;
        high = min(high, limit);

        // generate sieving primes using simple sieve of Eratosthenes
        for (; i * i <= high; i += 2)
            if (is_prime[i])
                for (int64_t j = i * i; j <= sqrt; j += i)
                    is_prime[j] = false;

        // initialize sieving primes for segmented sieve
        for (; s * s <= high; s += 2) {
            if (is_prime[s]) {
                primes.push_back(s);
                multiples.push_back(s * s - low);
            }
        }

        // sieve the current segment
        for (size_t i = 0; i < primes.size(); i++) {
            int64_t j = multiples[i];
            for (int64_t k = primes[i] * 2; j < segment_size; j += k)
                sieve[j] = false;
            multiples[i] = j - segment_size;
        }

        for (; n <= high; n += 2)
            if (sieve[n - low]) // n is a prime
                prim.push_back(n);
                //if(++count==501) cout<<n<<endl, count=1;
    }
}

int main() {
    Fast();
    segmented_sieve(1'000'000'000);
    int tc; cin >> tc;
    while(tc--)
    {
        ll l, r;
        cin >> l >> r;
        int low = lower_bound(prim.begin(), prim.end(), l) - prim.begin();
        int hi = upper_bound(prim.begin(), prim.end(), r) - prim.begin();
        while(low^hi)
        {
            cout << prim[low++] << endl;
        }
        cout << endl;
    }
}
