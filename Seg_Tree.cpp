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
 * Segment_Tree — Generic Segment Tree
 *
 * Template params:
 *   treeType = node/answer type  (default int)
 *   numsType = input array type  (default int)
 *   Base     = 0 → 0-indexed input, 1 → 1-indexed input
 *   Op       = binary functor for combine operation (default plus<treeType> = sum)
 *
 * Constructor:
 *   Segment_Tree<treeType, numsType, Base, Op> seg(
 *       int n,
 *       vector<numsType> nums = {},   // optional initial values
 *       Op op = Op{},                 // combine functor instance
 *       treeType def = treeType{}     // identity element
 *   );
 *
 * Methods:
 *   build(vector<numsType>& nums)       → rebuild from array (resets tree first)
 *   update(int index, numsType value)   → point update (1-indexed internally)
 *   query(int l, int r)                 → range query → treeType
 *   seg[index]                          → single element query
 *   size()                              → returns original n (not rounded size)
 *   print()                             → pretty tree debug print
 *
 * Example (sum, 0-indexed input — default):
 *   Segment_Tree<> seg(5, {1,2,3,4,5});
 *   seg.update(3, 10);
 *   cout << seg.query(1, 5);
 *
 * Example (custom op via lambda — name it first to use decltype):
 *   auto maxOp = [](int a, int b){ return max(a, b); };
 *   Segment_Tree<int, int, 0, decltype(maxOp)> seg(n, arr, maxOp, INT_MIN);
 *   cout << seg.query(1, n);
 *
 * Example (custom op via struct, 1-indexed input):
 *   struct GCD { int operator()(int a, int b) const { return __gcd(a, b); } };
 *   Segment_Tree<int, int, 1, GCD> seg(n, arr);
 *   cout << seg.query(1, n);
 */
template < typename treeType = int, typename numsType = int, int Base = 0,
           typename Op = plus < treeType > >
class Segment_Tree {
private:
    int n, N, max_level;
    treeType DEFAULT;
    vector < treeType > tree;
    Op operation;

    void build(const vector < numsType >& nums, int idx, int lx, int rx) {
        if (Base ? lx >= int(nums.size()) : lx > int(nums.size())) return;
        if (rx == lx) tree[idx] = treeType(nums[lx - !Base]);
        else {
            int mx = (rx + lx) / 2;
            build(nums, idx * 2, lx, mx);
            build(nums, idx * 2 + 1, mx + 1, rx);
            tree[idx] = operation(tree[idx * 2], tree[idx * 2 + 1]);
        }
    }

    void update(int index, numsType value, int idx, int lx, int rx) {
        if (rx == lx) tree[idx] = treeType(value);
        else {
            int mx = (rx + lx) / 2;
            if (index <= mx) update(index, value, idx * 2, lx, mx);
            else update(index, value, idx * 2 + 1, mx + 1, rx);
            tree[idx] = operation(tree[idx * 2], tree[idx * 2 + 1]);
        }
    }

    treeType query(int l, int r, int idx, int lx, int rx) const {
        if (lx > r || l > rx) return DEFAULT;
        if (lx >= l && rx <= r) return tree[idx];
        int mx = (lx + rx) / 2;
        return operation(query(l, r, idx * 2, lx, mx), query(l, r, idx * 2 + 1, mx + 1, rx));
    }

public:

    Segment_Tree(
        int n = 0,
        const vector < numsType >& nums = vector < numsType >(),
        Op op = Op{},
        treeType def = treeType{}
    ) : n(n), N(1), max_level(1), DEFAULT(def), operation(op) {
        while (N < n) N *= 2, max_level++;
        tree = vector < treeType > (2 * N, DEFAULT);
        if (!nums.empty()) build(nums, 1, 1, N);
    }

    // Rebuild from array — resets tree to DEFAULT first to avoid stale values
    void build(const vector < numsType >& nums) {
        std::fill(tree.begin(), tree.end(), DEFAULT);
        build(nums, 1, 1, N);
    }

    void update(int index, numsType value) {
        update(index, value, 1, 1, N);
    }

    treeType query(int l, int r) const {
        return query(l, r, 1, 1, N);
    }

    treeType operator[](int index) const {
        return query(index, index, 1, 1, N);
    }

    int size() const { return n; }

    void print() const {
        if (int(tree.size()) <= 1) return;
        int level = 0;
        queue < pair < int, int > > q;
        q.push({1, level});
        while (!q.empty()) {
            int nodesAtCurrentLevel = q.size();
            int spacesBetween = (1 << (max_level - level + 1)) - 1;
            int leadingSpaces = (1 << (max_level - level)) - 1;
            cout << string(leadingSpaces * 2, ' ');
            while (nodesAtCurrentLevel--) {
                auto [idx, lvl] = q.front();
                q.pop();
                cout << setw(2) << tree[idx];
                if (nodesAtCurrentLevel) cout << string(spacesBetween * 2, ' ');
                if (idx * 2 + 1 < int(tree.size())) {
                    q.push({idx * 2, lvl + 1});
                    q.push({idx * 2 + 1, lvl + 1});
                }
            }
            cout << "\n";
            level++;
        }
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
