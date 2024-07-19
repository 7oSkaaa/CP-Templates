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

template < typename treeType = int, typename numsType = int, int Base = 0 >
class Segment_Tree {
private:
    int size, max_level;
    treeType DEFAULT;
    vector < treeType > tree;
    const function < treeType(const treeType&, const treeType&) > operation;

    // Build the segment tree
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

    // Update the segment tree
    void update(int index, numsType value, int idx, int lx, int rx) {
        if (rx == lx) tree[idx] = treeType(value);
        else {
            int mx = (rx + lx) / 2;
            if (index <= mx) update(index, value, idx * 2, lx, mx);
            else update(index, value, idx * 2 + 1, mx + 1, rx);
            tree[idx] = operation(tree[idx * 2], tree[idx * 2 + 1]);
        }
    }

    // Query the segment tree
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
        const function < treeType(const treeType&, const treeType&) >& op = [](const treeType& a, const treeType& b) { return a + b; },
        treeType def = 0
    ) : size(1), max_level(1), DEFAULT(def), operation(op) {
        while (size < n) size *= 2, max_level++;
        tree = vector < treeType > (2 * size, DEFAULT);
        if (!nums.empty()) build(nums, 1, 1, size);
    }

    void build(const vector < numsType >& nums) {
        build(nums, 1, 1, size);
    }

    void update(int index, numsType value) {
        update(index, value, 1, 1, size);
    }

    treeType query(int l, int r) const {
        return query(l, r, 1, 1, size);
    }

    treeType operator[](int index) const {
        return query(index, index, 1, 1, size);
    }

    // Print the segment tree as a pretty tree structure
    void print() const {
        if (tree.size() <= 1) return;
        int level = 0;
        queue < pair < int, int > > q;  // pair of (index in tree, level in tree)
        q.push({1, level});
        while (!q.empty()) {
            int nodesAtCurrentLevel = q.size();
            int spacesBetween = (1 << (max_level - level + 1)) - 1;
            int leadingSpaces = (1 << (max_level - level)) - 1;
            cout << string(leadingSpaces * 2, ' ');  // leading spaces for the first node in the level
            while (nodesAtCurrentLevel--) {
                auto [idx, lvl] = q.front();
                q.pop();
                cout << setw(2) << tree[idx];
                // Print spaces between nodes at the current level
                if (nodesAtCurrentLevel) cout << string(spacesBetween * 2, ' ');
                // Add children to the queue
                if (idx * 2 < tree.size()) {
                    q.push({idx * 2, lvl + 1});
                    q.push({idx * 2 + 1, lvl + 1});
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