/**       In the name of Allah, the Gracious, the Merciful.
*               Praise be to Allah, Lord of the Worlds.
*               **************************************
*
*    I have not failed, I have just found 1000 WAYS that won't work.
*                 __________________________________
*                  Author  : Abd El-Twab  M. Fakhry
*                 __________________________________
*/

#include <ext/rope>
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

#define  read(arr, l, r)     for(int i = (l); i < (r); cin >> arr[i++])
#define  print(arr, l, r)    for(int i = (l); i < (r); cout << arr[i++] << " \n"[i == r])
#define  rep(i, l, r)        for (int i = l; i < r; i++)
#define  repr(i, r, l)       for (int i = r; i > l; i--)
#define  trav(a, x)          for (auto & a : x)
#define  Unique(n)           (n).erase(unique(all(n)), (n).end())
#define  endl                '\n'
#define  all(a)              a.begin() , a.end()
#define  NumberOfDigits(n)   ((int)log10(n) + 1)
#define  sz(a)               (int)a.size()
#define  rall(a)             a.rbegin(), a.rend()
#define  rsz(sz)             resize(sz)
#define  ins(x)              insert(x)
#define  debug(x)            cout << #x << " = " << (x) << '\n'
#define  LINE_ON             cout << "line Number = " << __LINE__ << endl
#define  RT(n)               return cout << (n) << endl, 0;
#define  clr(arr, x)         memset(arr, x, sizeof(arr))
#define  F                   first
#define  S                   second
#define  PB                  push_back
#define  EB                  emplace_back
#define  sqrt(n)             sqrtl(n)
#define  pow(a, b)           powl(a, b)
#define  get(n)              find_by_order(n)
#define  indexOf(n)          order_of_key(n)
#define  isPowerOfTwo(x)     (x && !(x & (x - 1)))
#define  Swap(n, k)           n ^= k, k ^= n, n ^= k;

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

typedef long long            ll;
typedef unsigned int         uint;
typedef unsigned long long   ull;

int dx8[8] = { 1, -1, 0, 0, 1, 1, -1, -1 }, dx4[4] = { 0, 0, 1,-1};
int dy8[8] = { 0, 0, 1, -1, 1, -1, 1, -1 }, dy4[4] = { 1,-1, 0, 0};

const double Pi = 2 * acos(0.0), Euler = 2.71828182845904523536,   Error = 1e-9, GoldenR = (1 + sqrtl(5.0)) / 2;
const int  MxsZ = (int)1e5 + 6,  ModP2 = (1 << 30) + 7, ModPT = (int)1e9+7,  oo = 0x3f3f3f3f;

template <class T>
T Gcd(T a, T b) { return b ? Gcd(b, a % b) : a; }

template <class T>
T Lcm(T a, T b) { return a / Gcd(a, b) * 1ll * b; }

template <class T>
using indexed_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update >;

template <class T>
using matrix = vector < vector <T> >;

template <class T>
using m_heap = priority_queue < T, vector < T >, greater < T > >;

template <class T>
string toString(T x) { stringstream sout; sout << x; return sout.str(); }

void Fast()
{
    cin.sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin.exceptions(cin.failbit);
}

void File()
{
    #ifdef FIN
    freopen("new.in", "r", stdin);
    #endif

    #ifdef FOUT
    freopen("output.out", "w", stdout);
    #endif
}

/**----------------------->>  Template  <<-----------------------**/

int t, cnt;
ll n;

struct Matrix
{
    ll a[2][2];

    Matrix()
    {
        rep(i, 0, 2) rep(j, 0, 2) a[i][j] = 0;
    }
};

Matrix mul(Matrix a, Matrix b)
{
    Matrix c = Matrix();
    rep(i, 0, 2) rep(j, 0, 2)
    {
        rep(k, 0, 2)
        c.a[i][j] = (c.a[i][j] + (a.a[i][k] * b.a[k][j]) % ModPT) % ModPT;
    }
    return c;
}

Matrix MatExp(Matrix a, ll p)
{
    if(!p)
    {
        Matrix m = Matrix();
        rep(i, 0, 2) m.a[i][i] = 1; //Identity Matrix
        return m;
    }
    if(p == 1) return a;

    if(p & 1)
        return mul(MatExp(a, p - 1), a);
    Matrix half = MatExp(a, p >> 1ll);

    return mul(half, half);
}

void Solve(Matrix Fib)
{
    cin >> n;
    Matrix Ans = MatExp(Fib, n);
    cout << "Case " << ++cnt << ": " << (Ans.a[0][0] * Ans.a[1][0]) % ModPT << endl;
}

/**------------------>>  Initialization gap  <<------------------**/

int main()
{
    Fast(); File();

    Matrix Fib = Matrix();
    Fib.a [0][0] = Fib.a [1][0] = Fib.a [0][1] = 1;
    Fib.a [1][1] = 0;

    cin >> t;
    while(t--) Solve(Fib);
}
