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
 *   T = value type (default int)
 *
 * Constructor:
 *   Fenwick_Tree<T> ft(int sz);   // 0-indexed input, size = sz
 *
 * Methods:
 *   build(vector<T>& nums)    → O(n) build from 0-indexed array
 *   add(int idx, T val)       → point update at 0-indexed idx
 *   query(int l, int r)       → range sum [l, r] 0-indexed → T
 *   get(int idx)              → value at single index
 *   size()                    → number of elements
 *
 * Example:
 *   Fenwick_Tree<int> ft(n);
 *   ft.build(arr);
 *   ft.add(3, 5);
 *   cout << ft.query(1, 4);
 *   cout << ft.get(3);
 */
template < typename T = int > struct Fenwick_Tree {

    int n;
    T DEFAULT;
    vector < T > tree;

    Fenwick_Tree(int sz = 0) : n(sz), DEFAULT(T{}) {
        tree.assign(n + 1, DEFAULT);
    }

    // O(n) build — faster than n individual add() calls
    void build(const vector < T >& nums) {
        for (int i = 0; i < sz(nums); i++) tree[i + 1] = nums[i];
        for (int i = 1; i <= n; i++) {
            int j = i + (i & -i);
            if (j <= n) tree[j] += tree[i];
        }
    }

    void add(int idx, T val) {
        for (++idx; idx <= n; idx += idx & -idx)
            tree[idx] += val;
    }

    T prefix(int idx) const {
        T ans = DEFAULT;
        for (++idx; idx > 0; idx -= idx & -idx)
            ans += tree[idx];
        return ans;
    }

    T query(int l, int r) const {
        if (l > r) return DEFAULT;
        return prefix(r) - (l ? prefix(l - 1) : DEFAULT);
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
