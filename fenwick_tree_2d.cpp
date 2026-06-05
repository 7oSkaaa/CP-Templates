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
 * Fenwick_Tree — 2D Binary Indexed Tree (BIT)
 *
 * Template params:
 *   T = value type (default int)
 *
 * Constructor:
 *   Fenwick_Tree<T> ft(int rows, int cols);   // 1-indexed rows and cols
 *
 * Methods:
 *   build(vector<vector<T>>& nums)           → build from 0-indexed 2D array
 *   add(int x, int y, T val)                → point update at (x, y) 1-indexed
 *   query(int x1, int y1, int x2, int y2)  → T, rectangle sum [x1..x2] × [y1..y2] 1-indexed
 *
 * Example:
 *   Fenwick_Tree<ll> ft(n, m);
 *   ft.build(grid);
 *   ft.add(2, 3, 5);
 *   cout << ft.query(1, 1, 2, 3);
 */
template < typename T = int > struct Fenwick_Tree {

    int n, m;
    T DEFAULT;
    vector < vector < T > > tree;

    Fenwick_Tree(int rows = 0, int cols = 0) : n(rows), m(cols), DEFAULT(T{}) {
        tree.assign(n + 1, vector < T >(m + 1, DEFAULT));
    }

    void build(const vector < vector < T > >& nums) {
        for (int i = 0; i < sz(nums); i++)
            for (int j = 0; j < sz(nums[0]); j++)
                add(i + 1, j + 1, nums[i][j]);
    }

    void add(int x, int y, T val) {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= m; j += j & -j)
                tree[i][j] += val;
    }

    T get_sum(int x, int y) const {
        T s = DEFAULT;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j)
                s += tree[i][j];
        return s;
    }

    T query(int x1, int y1, int x2, int y2) const {
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        return get_sum(x2, y2) - get_sum(x1 - 1, y2)
             - get_sum(x2, y1 - 1) + get_sum(x1 - 1, y1 - 1);
    }
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
