#include <bits/stdc++.h>

using namespace std;

#define fixed(n) fixed << setprecision(n)
#define ceil(n, m) (((n) + (m) - 1) / (m))
#define add_mod(a, b, m) (((a % m) + (b % m)) % m)
#define sub_mod(a, b, m) (((a % m) - (b % m) + m) % m)
#define mul_mod(a, b, m) (((a % m) * (b % m)) % m)
#define all(vec) vec.begin(), vec.end()
#define rall(vec) vec.rbegin(), vec.rend()
#define sz(x) int(x.size())
#define debug(x) cout << #x << ": " << (x) << "\n";
#define fi first
#define se second
#define ll long long
#define ull unsigned long long
#define EPS 1e-9
constexpr int INF = 1 << 30, Mod = 1e9 + 7;
constexpr ll LINF = 1LL << 62;
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
 * SegmentTree2D — 2D Segment Tree (point update, rectangle query)
 *
 * Template params:
 *   T    = value type          (default int)
 *   Base = 0 → 0-indexed input, 1 → 1-indexed input
 *   Op   = binary combine functor (default plus<T> = sum)
 *
 * Constructors:
 *   SegmentTree2D<T, Base> seg(int n, int m);
 *   SegmentTree2D<T, Base> seg(int n, int m, vector<vector<T>>& nums);
 *
 * Methods:
 *   update(int x, int y, T val)             → point update
 *   query(int lx, int rx, int ly, int ry)   → T, rectangle result [lx..rx] × [ly..ry]
 *   get(int x, int y)                       → T, single cell value
 *   rows_size()                             → original n
 *   cols_size()                             → original m
 *
 * Example (sum, 0-indexed):
 *   SegmentTree2D<int> seg(n, m, grid);
 *   seg.update(2, 3, 7);
 *   cout << seg.query(1, 3, 1, 4);
 *
 * Example (custom op via lambda):
 *   auto maxOp = [](int a, int b){ return max(a, b); };
 *   SegmentTree2D<int, 0, decltype(maxOp)> seg(n, m, grid, maxOp, INT_MIN);
 */
template < typename T = int, int Base = 0, typename Op = plus < T > >
struct SegmentTree2D {

    int n, m, rows, cols;
    T DEFAULT;
    vector < vector < T > > tree;
    Op operation;

    static constexpr int L(int i) { return i << 1; }
    static constexpr int R(int i) { return (i << 1) | 1; }

    void init(int n_, int m_) {
        n = n_; m = m_;
        rows = 1; cols = 1;
        while (rows < n) rows *= 2;
        while (cols < m) cols *= 2;
        tree.assign(2 * rows, vector < T >(2 * cols, DEFAULT));
    }

    SegmentTree2D(int n = 0, int m = 0, Op op = Op{}, T def = T{})
        : DEFAULT(def), operation(op) { init(n, m); }

    SegmentTree2D(int n, int m, const vector < vector < T > >& nums, Op op = Op{}, T def = T{})
        : DEFAULT(def), operation(op) { init(n, m); build(nums); }

    void build_y(int vx, int lx, int rx, int vy, int ly, int ry, const vector < vector < T > >& vec) {
        if (Base ? lx >= sz(vec) : lx > sz(vec)) return;
        if (Base ? ly >= sz(vec[0]) : ly > sz(vec[0])) return;
        if (ly == ry) {
            if (lx == rx) tree[vx][vy] = vec[lx - !Base][ly - !Base];
            else tree[vx][vy] = operation(tree[L(vx)][vy], tree[R(vx)][vy]);
        } else {
            int my = (ly + ry) / 2;
            build_y(vx, lx, rx, L(vy), ly, my, vec);
            build_y(vx, lx, rx, R(vy), my + 1, ry, vec);
            tree[vx][vy] = operation(tree[vx][L(vy)], tree[vx][R(vy)]);
        }
    }

    void build_x(int vx, int lx, int rx, const vector < vector < T > >& vec) {
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            build_x(L(vx), lx, mx, vec);
            build_x(R(vx), mx + 1, rx, vec);
        }
        build_y(vx, lx, rx, 1, 1, cols, vec);
    }

    // Resets tree to DEFAULT before rebuilding to avoid stale values
    void build(const vector < vector < T > >& vec) {
        for (auto& row : tree) fill(row.begin(), row.end(), DEFAULT);
        build_x(1, 1, rows, vec);
    }

    T query_y(int vx, int vy, int ly0, int ry0, int ly, int ry) const {
        if (ly > ry) return DEFAULT;
        if (ly == ly0 && ry0 == ry) return tree[vx][vy];
        int my = (ly0 + ry0) / 2;
        return operation(
            query_y(vx, L(vy), ly0, my, ly, min(ry, my)),
            query_y(vx, R(vy), my + 1, ry0, max(ly, my + 1), ry)
        );
    }

    T query_x(int vx, int lx0, int rx0, int lx, int rx, int ly, int ry) const {
        if (lx > rx) return DEFAULT;
        if (lx == lx0 && rx0 == rx) return query_y(vx, 1, 1, cols, ly, ry);
        int mx = (lx0 + rx0) / 2;
        return operation(
            query_x(L(vx), lx0, mx, lx, min(rx, mx), ly, ry),
            query_x(R(vx), mx + 1, rx0, max(lx, mx + 1), rx, ly, ry)
        );
    }

    T query(int lx, int rx, int ly, int ry) const {
        return query_x(1, 1, rows, lx, rx, ly, ry);
    }

    void update_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, T val) {
        if (ly == ry) {
            if (lx == rx) tree[vx][vy] = val;
            else tree[vx][vy] = operation(tree[L(vx)][vy], tree[R(vx)][vy]);
        } else {
            int my = (ly + ry) / 2;
            if (y <= my) update_y(vx, lx, rx, L(vy), ly, my, x, y, val);
            else update_y(vx, lx, rx, R(vy), my + 1, ry, x, y, val);
            tree[vx][vy] = operation(tree[vx][L(vy)], tree[vx][R(vy)]);
        }
    }

    void update_x(int vx, int lx, int rx, int x, int y, T val) {
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            if (x <= mx) update_x(L(vx), lx, mx, x, y, val);
            else update_x(R(vx), mx + 1, rx, x, y, val);
        }
        update_y(vx, lx, rx, 1, 1, cols, x, y, val);
    }

    void update(int x, int y, T val) {
        update_x(1, 1, rows, x, y, val);
    }

    T get(int x, int y) const {
        return query(x, x, y, y);
    }

    int rows_size() const { return n; }
    int cols_size() const { return m; }
};

void Solve(){

}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int test_cases = 1;
    // cin >> test_cases;
    for(int tc = 1; tc <= test_cases; tc++){
        // cout << "Case #" << tc << ": ";
        Solve();
    }
    return 0;
}
