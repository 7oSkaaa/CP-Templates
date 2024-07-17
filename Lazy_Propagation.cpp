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

template < typename T = int , const int Base = 0 >
class Lazy_Propagation {
private:
    struct Node {
        T val, update;
        bool is_lazy;
        Node(T V = 0) : val(V), update(0), is_lazy(false) {}
    };

    int size, max_level;
    T query_default, init_default;
    vector < Node > tree;

    // Lazy operation function
    T lazy_operation(T a, T b) {
        return a + b; // Change this to your specific lazy operation
    }

    // Tree operation function
    Node tree_operation(const Node& a, const Node& b) {
        return Node(a.val + b.val); // Change this to your specific tree operation
    }

    // Push lazy value to children
    void propagate(int idx, int lx, int rx) {
        if (!tree[idx].is_lazy) return;
        tree[idx].val = lazy_operation(tree[idx].val, (rx - lx + 1) * tree[idx].update);
        if (lx != rx) {
            tree[idx * 2].update = lazy_operation(tree[idx * 2].update, tree[idx].update);
            tree[idx * 2 + 1].update = lazy_operation(tree[idx * 2 + 1].update, tree[idx].update);
            tree[idx * 2].is_lazy = tree[idx * 2 + 1].is_lazy = true;
        }
        tree[idx].update = init_default;
        tree[idx].is_lazy = false;
    }

    // Update lazy value
    void update_lazy(int idx, T v) {
        tree[idx].update = lazy_operation(tree[idx].update, v);
        tree[idx].is_lazy = true;
    }

    // Build tree with initial value or vector of values
    void build(const vector<T>& nums, const T initial_value, int idx, int lx, int rx) {
        if (!nums.empty() && (Base ? lx >= int(nums.size()) : lx > int(nums.size()))) return;
        if (rx == lx) tree[idx] = !nums.empty() ? Node(nums[lx - !Base]) : Node(initial_value);
        else {
            int mx = (lx + rx) / 2;
            build(nums, initial_value, idx * 2, lx, mx);
            build(nums, initial_value, idx * 2 + 1, mx + 1, rx);
            propagate(idx * 2, lx, mx);
            propagate(idx * 2 + 1, mx + 1, rx);
            tree[idx] = tree_operation(tree[idx * 2], tree[idx * 2 + 1]);
        }
    }

    void update(int l, int r, T v, int idx, int lx, int rx) {
        propagate(idx, lx, rx);
        if (lx >= l && rx <= r) return update_lazy(idx, v);
        if (lx > r || rx < l) return;
        int mx = (lx + rx) / 2;
        update(l, r, v, idx * 2, lx, mx);
        update(l, r, v, idx * 2 + 1, mx + 1, rx);
        propagate(idx * 2, lx, mx);
        propagate(idx * 2 + 1, mx + 1, rx);
        tree[idx] = tree_operation(tree[idx * 2], tree[idx * 2 + 1]);
    }

    T query(int l, int r, int idx, int lx, int rx) {
        propagate(idx, lx, rx);
        if (lx >= l && rx <= r) return tree[idx].val;
        if (lx > r || rx < l) return query_default;
        int mx = (lx + rx) / 2;
        T left_result = query(l, r, idx * 2, lx, mx);
        T right_result = query(l, r, idx * 2 + 1, mx + 1, rx);
        return lazy_operation(left_result, right_result);
    }

public:

    Lazy_Propagation(int n, const vector < T >& v = vector < T > ()) : size(1), max_level(1), query_default(0), init_default(0)  {
        while (size <= n) size *= 2, max_level++;
        tree = vector < Node > (2 * size, Node(init_default));
        if (!v.empty()) build(v);
    }

    void build(const T initial_value) {
        build(vector < T >(), initial_value, 1, 1, size);
    }

    void build(const vector < T >& nums) {
        build(nums, init_default, 1, 1, size);
    }

    void update(int i, T v) {
        update(i, i, v, 1, 1, size);
    }

    void update(int l, int r, T v) {
        update(l, r, v, 1, 1, size);
    }

    T query(int l, int r) {
        return query(l, r, 1, 1, size);
    }

    T get(int i) {
        return query(i, i, 1, 1, size);
    }

    void print() {
        if (tree.size() <= 1) return;
        int level = 0;
        queue < tuple<int, int, int, int> > q;  // pair of (index in tree, level in tree, lx, rx)
        q.push({1, level, 1, size});
        while (!q.empty()) {
            int nodesAtCurrentLevel = q.size();
            int spacesBetween = (1 << (max_level - level + 1)) - 1;
            int leadingSpaces = (1 << (max_level - level)) - 1;
            cout << string(leadingSpaces * 2, ' ');
            while (nodesAtCurrentLevel--) {
                auto [idx, lvl, lx, rx] = q.front();
                q.pop();            
                // Propagate lazy values
                propagate(idx, lx, rx);
                cout << setw(2) << tree[idx].val;
                // Print spaces between nodes at the current level
                if (nodesAtCurrentLevel) cout << string(spacesBetween * 2, ' ');
                // Add children to the queue
                if (idx * 2 < tree.size()) {
                    int mx = (lx + rx) / 2;
                    q.push({idx * 2, lvl + 1, lx, mx});
                    q.push({idx * 2 + 1, lvl + 1, mx + 1, rx});
                }
            }
            cout << "\n";  // new line for the new level
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