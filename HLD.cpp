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

template < typename T = int, const int VAL_ON_EDGE = 0 > struct HLD {

    const vector < vector < T > > &adj;
    vector < T > dep, par, root, pos, SubtreeSz, child;
    int nxtPos;

    HLD(int n, const vector < vector < T > >& G, int treeRoot = 1) : adj(G) {
        nxtPos = 1;
        // child is heavy child
        dep = par = root = pos = SubtreeSz = child = vector < T > (n + 5);
        init(treeRoot);
        build(treeRoot);
    }

    void init(int u, int p = -1, int d = 0){
        dep[u] = d, par[u] = p, SubtreeSz[u] = 1;
        for (int v : adj[u]){ 
            if (v == p) continue;
            init(v, u, d + 1);
            SubtreeSz[u] += SubtreeSz[v];
            if (SubtreeSz[v] > SubtreeSz[child[u]]) 
                child[u] = v;
        }
    }

    void build(int u, bool newChain = true){
        root[u] = newChain ? u : root[par[u]];
        pos[u] = nxtPos++;
        if (child[u]) 
            build(child[u], false);
        for (int v : adj[u]){
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