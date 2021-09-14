#include <algorithm>
#include <functional>
#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

#define endl '\n'

#define debug(args...)				\
  {						\
    string _s = #args;				\
    replace(_s.begin(), _s.end(), ',', ' ');	\
    stringstream _ss(_s);			\
    istream_iterator<string> _it(_ss);		\
    err(_it, args);				\
  }

using namespace std;

using i128 = __int128_t;
using i64 = int64_t;
using i32 = int32_t;

using u128 = __uint128_t;
using u64 = uint64_t;
using u32 = uint32_t;
using ld = long double;

const int N = 2e5 + 9, M = N << 1, oo = 0x3f3f3f3f, Mod = 1e9 + 7;
const ld eps = 1e-18;
const i64 INF = 0x3f3f3f3f3f3f3f3f;

void err(istream_iterator<string> it) {}
template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " = " << a << endl;
  err(++it, args...);
}

void fast() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}

void file() {
  // freopen("input.in", "r", stdin);
  freopen("output.out", "w", stdout);
}

i64 Bin_Exp(i128 a, i64 p) {
  i64 res = 1;
  for (res = 1; p; p >>= 1) {
    if (p & 1)
      res *= a;
    a *= a;
  }
  return res;
}

i64 Gcd(i64 a, i64 b) {
  if(!a)
    return b;

  u64 shift = __builtin_ctzl(a | b);
  a >>= __builtin_ctzl(a);

  while(b > 0) {
    b >>= __builtin_ctzl(b);
    if(a > b)
      swap(a, b);
    b -= a;
  }
  return a << shift;
}

i64 n, k;

void Solve() {
  while(cin >> n >> k && ~n && ~k) {
    i64 total_probability = ((n * (n - 1)) >> 1);
    i64 chances = ((k - 1) >> 1);
    chances = (chances * (chances + 1));

    if(k & 1ll)
      chances -= ((k - 1) >> 1);

    i64 gcd = Gcd(chances, total_probability);
    chances /= gcd;
    total_probability /= gcd;

    if(chances == 0) {
      cout << chances << endl;
    } else if (chances == total_probability) {
      cout << chances << endl;
    } else {
      cout << chances << '/' << total_probability << endl;
    }
  }
}

int main() {
  fast();
  // file();

  int t = 1; // cin >> t;
  for (int i = 1; i <= t; ++i) {
    Solve();
  }
}
