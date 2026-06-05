#include <bits/stdc++.h>

using namespace std;

#define cin_2d(vec, n, m) for(int i = 0; i < n; i++) for(int j = 0; j < m && cin >> vec[i][j]; j++);
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define fixed(n) fixed << setprecision(n)
#define ceil(n, m) (((n) / (m)) + ((n) % (m) ? 1 : 0))
#define fill(vec, value) memset(vec, value, sizeof(vec));
#define mul_mod(a, b, m) (((a % m) * (b % m)) % m)
#define add_mod(a, b, m) (((a % m) + (b % m)) % m)
#define all(vec) vec.begin(), vec.end()
#define rall(vec) vec.rbegin(), vec.rend()
#define sz(x) int(x.size())
#define debug(x) cout << #x << ": " << (x) << "\n";
#define fi first
#define se second
#define ll long long
#define ull unsigned long long
#define Mod  1'000'000'007
#define OO 2'000'000'000
#define EPS 1e-9
#define PI acos(-1)
template < typename T = int > using Pair = pair < T, T >;
vector < string > RET = {"NO", "YES"};

template < typename T = int > istream& operator >> (istream &in, vector < T > &v) {
    for (auto &x : v) in >> x;
    return in;
}

template < typename T = int > ostream& operator << (ostream &out, const vector < T > &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}

/*
 * Fenwick_Tree — Binary Indexed Tree (BIT), 1D
 *
 * Template params:
 *   T      = value type                    (default int)
 *   Op     = combine operation             (default plus<T>  = sum)
 *   InvOp  = inverse of Op for range query (default minus<T> = subtract)
 *
 * IMPORTANT — Op must be invertible via InvOp:
 *   query(l, r) = prefix(r) [InvOp] prefix(l-1)
 *   This requires: InvOp(Op(a, b), b) == a  for all a, b
 *
 * Allowed operations:
 *   Sum        : Op = plus<T>,     InvOp = minus<T>      — identity = 0  (default)
 *   XOR        : Op = bit_xor<T>,  InvOp = bit_xor<T>   — identity = 0  (self-inverse)
 *   Mul mod p  : custom Op/InvOp with modular inverse    — identity = 1
 *
 * NOT allowed (no inverse exists):
 *   max, min, gcd, bitwise AND/OR
 *   → use Segment Tree for those
 *
 * Constructor:
 *   Fenwick_Tree<T, Op, InvOp> ft(int sz, Op op = {}, InvOp inv = {}, T identity = T{});
 *
 * Methods:
 *   build(vector<T>& nums)    → O(n) build from 0-indexed array
 *   add(int idx, T val)       → point update at 0-indexed idx
 *   query(int l, int r)       → range result [l, r] 0-indexed → T
 *   get(int idx)              → value at single index
 *   size()                    → number of elements
 *
 * Example (sum — default):
 *   Fenwick_Tree<int> ft(n, arr);
 *   ft.add(3, 5);
 *   cout << ft.query(1, 4);
 *
 * Example (XOR — self-inverse, use decltype for lambdas):
 *   Fenwick_Tree<int, bit_xor<int>, bit_xor<int>> ft(n);
 *   ft.build(arr);
 *   cout << ft.query(0, n - 1);
 *
 * Example (custom lambda op):
 *   auto myOp  = [](int a, int b){ return a ^ b; };
 *   auto myInv = [](int a, int b){ return a ^ b; };
 *   Fenwick_Tree<int, decltype(myOp), decltype(myInv)> ft(n, myOp, myInv, 0);
 */
template < typename T = int, typename Op = plus < T >, typename InvOp = minus < T > >
struct Fenwick_Tree {

    int n;
    T DEFAULT;
    Op op;
    InvOp inv_op;
    vector < T > tree;

    Fenwick_Tree(int sz = 0, Op op = Op{}, InvOp inv_op = InvOp{}, T def = T{})
        : n(sz), DEFAULT(def), op(op), inv_op(inv_op) {
        tree.assign(n + 1, DEFAULT);
    }

    // O(n) build — faster than n individual add() calls
    void build(const vector < T >& nums) {
        for (int i = 0; i < sz(nums); i++) tree[i + 1] = nums[i];
        for (int i = 1; i <= n; i++) {
            int j = i + (i & -i);
            if (j <= n) tree[j] = op(tree[j], tree[i]);
        }
    }

    void add(int idx, T val) {
        for (++idx; idx <= n; idx += idx & -idx)
            tree[idx] = op(tree[idx], val);
    }

    T prefix(int idx) const {
        T ans = DEFAULT;
        for (++idx; idx > 0; idx -= idx & -idx)
            ans = op(ans, tree[idx]);
        return ans;
    }

    T query(int l, int r) const {
        if (l > r) return DEFAULT;
        return inv_op(prefix(r), l ? prefix(l - 1) : DEFAULT);
    }

    T get(int idx) const {
        return query(idx, idx);
    }

    int size() const { return n; }
};

void Solve(){

}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--)
        Solve();
    return 0;
}
