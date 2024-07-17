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
        const function < treeType(const treeType&, const treeType&) >& op = [](const treeType& a, const treeType& b) { return a + b; }
    ) : size(1), max_level(1), DEFAULT(0), operation(op) {
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

template < typename T = int, const int VAL_ON_EDGE = 0 > struct HLD {
    // VAL_ON_EDGE = 0 if value on nodes
    // VAL_ON_EDGE = 1 if value on edges

    const vector < vector < Pair < T > > > &adj;
    vector < T > dep, par, root, pos, SubtreeSz, child;
    int nxtPos;
    Segment_Tree < T > seg;

    #define loop(v, w, ADJ) for(auto [v, w] : ADJ)

    HLD(int n, const vector < vector < Pair < T > > >& G, int treeRoot = 1) : adj(G) {
        nxtPos = 1;
        // child is heavy child
        dep = par = root = pos = SubtreeSz = child = vector < T > (n + 5);
        init(treeRoot);
        build(treeRoot);
        seg = Segment_Tree < T > (n + 5);
    }

    // init the tree
    void init(int u, int p = -1, int d = 0){
        dep[u] = d, par[u] = p, SubtreeSz[u] = 1;
        loop(v, w, adj[u]){
            if (v == p) continue;
            init(v, u, d + 1);
            SubtreeSz[u] += SubtreeSz[v];
            if (SubtreeSz[v] > SubtreeSz[child[u]]) 
                child[u] = v;
        }
    } 

    // get the root of the chain
    int get_lca(int u, int v){
        while (root[u] != root[v]){
            if (dep[root[u]] < dep[root[v]]) 
                swap(u, v);
            u = par[root[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    // build the chains
    void build(int u, bool newChain = true){
        root[u] = newChain ? u : root[par[u]];
        pos[u] = nxtPos++;
        if (child[u]) 
            build(child[u], false);
        loop(v, w, adj[u]){
            if(v == par[u] || v == child[u]) continue;
            build(v, true);
        }
    }

    // make u lower
    void makeULower(int& u, int& v){
        if(dep[root[u]] < dep[root[v]] || (root[u] == root[v] && dep[u] < dep[v]))
            swap(u, v);
    }

    // move up the chain and also change the next position
    Pair < T > moveUp(int& u){
        Pair < T > ret = {pos[root[u]], pos[u]};
        u = par[root[u]];
        return ret;
    }

    vector < Pair < T > > queryPath(int u, int v){
        // return all ranges in segment tree
        vector < Pair < T > > ret;
        while(root[u] != root[v]){
            makeULower(u, v);
            ret.push_back(moveUp(u));
        }
        // add range between u and v
        makeULower(u, v);
        if(!VAL_ON_EDGE) // value on nodes
            ret.push_back({pos[v], pos[u]});
        else if(u != v) // don't include the root node
            ret.push_back({pos[v] + 1, pos[u]});
        return ret;
    }

    // get child of a node for problem that value on edges
    int getChild(int u, int v){
        if(par[u] == v) 
            return u;
        return v;
    }

    // update value of node u
    void update(int u, T val){
        seg.update(pos[u], val);
    }

    // update value of edge u-v
    void update(int u, int v, T val){
        u = getChild(u, v);
        seg.update(pos[u], val);
    }

    // query value
    T query(int u_q, int v_q){
        T ret = 0;
        for(auto& [u, v] : queryPath(u_q, v_q))
            ret = max(ret, seg.query(u, v));
        return ret;
    }

    #undef loop
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