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

template < typename T = int > struct LCA {
    
    struct Edge {

        T v, w;

        Edge(T V = 0, T W = 0) : v(V), w(W) {}

        bool operator < (const Edge &rhs) const {
            return w < rhs.w;
        }

    };

    int N, LOG;
    vector < vector < T > > anc, cost;
    vector < vector < Edge > > adj;
    vector < int > dep;
    
    LCA(int n){
        N = n + 10, LOG = 0;
        while((1 << LOG) <= N) LOG++;
        dep = vector < int > (N);
        adj = vector < vector < Edge > > (N);
        anc = cost = vector < vector < T > > (N, vector < T > (LOG));
    }
    
    void add_edge(int u, int v, T w){
        adj[u].push_back(Edge(v, w));
        adj[v].push_back(Edge(u, w));
    }

    void build_adj(int edges){
        for(int i = 0, u, v, w; i < edges && cin >> u >> v >> w; i++)
            add_edge(u, v, w);
    }

    T operation(T a, T b){
        return a + b;
    }
    
    void dfs(int u, int p = 0){
        for(auto& [v, w] : adj[u]){
            if(v == p) continue;
            dep[v] = dep[u] + 1, anc[v][0] = u, cost[v][0] = w;
            for(int bit = 1; bit < LOG; bit++){
                anc[v][bit] = anc[anc[v][bit - 1]][bit - 1];
                cost[v][bit] = operation(cost[v][bit - 1], cost[anc[v][bit - 1]][bit - 1]);
            }
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
    
    T get_cost(int u, int dist){
        if(dep[u] < dist) return -1;
        T ans = 0;
        for(int bit = 0; bit < LOG; bit++)
            if(dist & (1 << bit))
                ans = operation(ans, cost[u][bit]), u = anc[u][bit];
        return ans;
    }
    
    T query(int u, int v){
        int lca = get_lca(u, v);
        return operation(get_cost(u, dep[u] - dep[lca]), get_cost(v, dep[v] - dep[lca]));
    }

    void build(int root = 1){
        dfs(root);
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