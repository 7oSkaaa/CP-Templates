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
 * Lazy_Propagation — Segment Tree with Lazy Propagation
 *
 * Edit only the CUSTOMIZE block. Everything else is framework.
 *
 * Default: range add updates, range sum queries (1-indexed).
 *
 * Constructor: Lazy_Propagation seg(int n, vector<T> v = {})
 *
 * Methods:
 *   update(int l, int r, Lazy v)  — range update [l, r]
 *   update(int i,        Lazy v)  — point update at i
 *   query (int l, int r) → T      — range query  [l, r]
 *   operator[](int i)    → T      — single element query
 *
 * Common customizations:
 *   Range assign, range min  →  combine: min(a,b)   apply: lz          compose: new_lz
 *   Range add,    range min  →  combine: min(a,b)   apply: val+lz      compose: old_lz+new_lz
 *   Range add,    range sum  →  combine: a+b        apply: val+lz*len  compose: old_lz+new_lz  ← default
 */
struct Lazy_Propagation {

    // ═══ CUSTOMIZE ════════════════════════════════════════════════════════════
    using T = ll;    // node value type
    using Lazy = ll; // lazy update type (can differ from T)

    T IDENTITY = 0;    // identity for combine (0 for sum, INF for min)
    Lazy LAZY_ID = 0;  // "no pending update"  (0 for add, LLONG_MIN for assign)

    T combine(T a, T b) { return a + b; }
    T apply(T val, Lazy lz, int len) { return val + lz * len; }
    Lazy compose(Lazy old_lz, Lazy new_lz) { return old_lz + new_lz; }
    // ══════════════════════════════════════════════════════════════════════════

    struct Node {
        T val;
        Lazy lazy;
    };

    int n;
    vector < Node > tree;

    Lazy_Propagation(int n, const vector < T > &v = vector < T > ())
        : n(n), tree(4 * n + 4, {IDENTITY, LAZY_ID}) {
        if (!v.empty()) build(v, 1, 1, n);
    }

private:

    void push_up(int idx) {
        tree[idx].val = combine(tree[idx * 2].val, tree[idx * 2 + 1].val);
    }

    void apply_node(int idx, int lx, int rx, Lazy lz) {
        tree[idx].val = apply(tree[idx].val, lz, rx - lx + 1);
        tree[idx].lazy = compose(tree[idx].lazy, lz);
    }

    void push_down(int idx, int lx, int rx) {
        if (tree[idx].lazy == LAZY_ID) return;
        int mid = (lx + rx) / 2;
        apply_node(idx * 2, lx, mid, tree[idx].lazy);
        apply_node(idx * 2 + 1, mid + 1, rx, tree[idx].lazy);
        tree[idx].lazy = LAZY_ID;
    }

    void build(const vector < T > &v, int idx, int lx, int rx) {
        if (lx == rx) {
            tree[idx] = {lx <= sz(v) ? v[lx - 1] : IDENTITY, LAZY_ID};
            return;
        }
        int mid = (lx + rx) / 2;
        build(v, idx * 2, lx, mid);
        build(v, idx * 2 + 1, mid + 1, rx);
        push_up(idx);
    }

    void update(int l, int r, Lazy v, int idx, int lx, int rx) {
        if (lx >= l && rx <= r) { apply_node(idx, lx, rx, v); return; }
        if (lx > r || rx < l) return;
        push_down(idx, lx, rx);
        int mid = (lx + rx) / 2;
        update(l, r, v, idx * 2, lx, mid);
        update(l, r, v, idx * 2 + 1, mid + 1, rx);
        push_up(idx);
    }

    T query(int l, int r, int idx, int lx, int rx) {
        if (lx >= l && rx <= r) return tree[idx].val;
        if (lx > r || rx < l) return IDENTITY;
        push_down(idx, lx, rx);
        int mid = (lx + rx) / 2;
        return combine(
            query(l, r, idx * 2, lx, mid),
            query(l, r, idx * 2 + 1, mid + 1, rx)
        );
    }

public:

    void update(int l, int r, Lazy v) { update(l, r, v, 1, 1, n); }
    void update(int i, Lazy v) { update(i, i, v, 1, 1, n); }
    T query(int l, int r) { return query(l, r, 1, 1, n); }
    T operator[](int i) { return query(i, i, 1, 1, n); }
};

void Solve() {

}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int test_cases = 1;
    // cin >> test_cases;
    for (int tc = 1; tc <= test_cases; tc++) {
        // cout << "Case #" << tc << ": ";
        Solve();
    }
    return 0;
}
