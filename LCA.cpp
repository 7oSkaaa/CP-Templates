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

template < typename T = int > struct LCA {
    
    int N, LOG;
    vector < vector < T > > anc;
    vector < vector < T > > adj;
    vector < int > dep;
    
    LCA(int n = 0){
        N = n + 10, LOG = 0;
        while((1 << LOG) <= N) LOG++;
        dep = vector < int > (N);
        adj = vector < vector < T > > (N);
        anc = vector < vector < T > > (N, vector < T > (LOG));
    }

    LCA(int n, const vector < vector < T > > &G) : adj(G){ 
        N = n + 10, LOG = 0;
        while((1 << LOG) <= N) LOG++;
        dep = vector < int > (N);
        anc = vector < vector < T > > (N, vector < T > (LOG));
    }

    void add_edge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build_adj(int edges){
        for(int i = 0, u, v; i < edges && cin >> u >> v; i++)
            add_edge(u, v);
    }

    void dfs(int u, int p = 0){
        for(auto& v : adj[u]){
            if(v == p) continue;
            dep[v] = dep[u] + 1, anc[v][0] = u;
            for(int bit = 1; bit < LOG; bit++)
                anc[v][bit] = anc[anc[v][bit - 1]][bit - 1];
            dfs(v, u);
        }
    }
    
    int kth_ancestor(int u, int k){
        if(dep[u] < k) 
            return -1;
        for(int bit = LOG - 1; bit >= 0; bit--)
            if(k & (1 << bit))
                u = anc[u][bit];
        return u;
    }
    
    int get_lca(int u, int v){
        if(dep[u] < dep[v])
            swap(u, v);
        u = kth_ancestor(u, dep[u] - dep[v]);
        if(u == v)
            return u;
        for(int bit = LOG - 1; bit >= 0; bit--)
            if(anc[u][bit] != anc[v][bit])
                u = anc[u][bit], v = anc[v][bit];
        return anc[u][0];
    }

    T query(int u, int v){
        int lca = get_lca(u, v);
        return dep[u] + dep[v] - 2 * dep[lca];
    }

    void build(int root = 1){
        dfs(root);
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