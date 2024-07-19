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

template < typename T = int, bool VAL_ON_EDGE = false >
class HLD {
    // VAL_ON_EDGE = 1 if the value is on the edge, 0 if the value is on the node
private:
    const vector < vector < int > > & adj;
    vector < int >  dep, par, root, pos, SubtreeSz, child;
    int nxtPos;

    void init(int u, int p = -1, int d = 0) {
        dep[u] = d, par[u] = p, SubtreeSz[u] = 1;
        for (auto& v : adj[u]) {
            if (v == p) continue;
            init(v, u, d + 1);
            SubtreeSz[u] += SubtreeSz[v];
            if (SubtreeSz[v]  >  SubtreeSz[child[u]]) 
                child[u] = v;
        }
    }

    void build(int u, bool newChain = true) {
        root[u] = newChain ? u : root[par[u]];
        pos[u] = nxtPos++;
        if (child[u]) build(child[u], false);
        for (auto& v : adj[u]) {
            if (v == par[u] || v == child[u]) continue;
            build(v, true);
        }
    }

    void makeULower(int& u, int& v) {
        if (dep[root[u]]  <  dep[root[v]] || (root[u] == root[v] && dep[u]  <  dep[v]))
            swap(u, v);
    }

    pair < int, int >  moveUp(int& u) {
        pair < int, int >  ret = {pos[root[u]], pos[u]};
        u = par[root[u]];
        return ret;
    }

    vector < pair < int, int >  >  queryPath(int u, int v) {
        vector < pair < int, int >  >  ret;
        while (root[u] != root[v]) {
            makeULower(u, v);
            ret.push_back(moveUp(u));
        }
        makeULower(u, v);
        if (!VAL_ON_EDGE) 
            ret.push_back({pos[v], pos[u]});
        else if (u != v) 
            ret.push_back({pos[v] + 1, pos[u]});
        return ret;
    }

    int getChild(int u, int v) {
        if (par[u] == v) return u;
        return v;
    }

public:
    HLD(
        int n, 
        const vector < vector < int  >  > & G, 
        int treeRoot = 1
    ) : adj(G), dep(n + 5), par(n + 5), root(n + 5), pos(n + 5), SubtreeSz(n + 5), child(n + 5), nxtPos(1) {
        init(treeRoot);
        build(treeRoot);
    }

    void update(int u, T val, const function < void(T, T) >  & update) {
        update(pos[u], val);
    }

    void update(int u, int v, T val, const function < void(T, T) >  & update) {
        u = getChild(u, v);
        update(pos[u], val);
    }

    T query(
        int u_q, 
        int v_q, 
        const function < T(T, T) >  & operation, 
        const function < T(T, T) >  & query,
        const T default_value
    ) {
        T ret = default_value;
        for (auto& [u, v] : queryPath(u_q, v_q))
            ret = operation(ret, query(u, v));
        return ret;
    }
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