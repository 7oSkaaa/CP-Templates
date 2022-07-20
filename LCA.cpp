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

vector < int > dep;
vector < vector < Pair < int > > > adj; 
vector < vector < int > > anc, cost;

void init(int n){
    n += 10;
    dep = vector < int > (n, 0);
    adj = vector < vector < Pair < int > > > (n);
    anc = cost = vector < vector < int > > (n, vector < int > (20, 0));
}

int k_ancestor(int node, int dist){
    if(dep[node] <= dist) return -1;
    for(int bit = 0; bit < 20; bit++)
        if(dist & (1 << bit))
            node = anc[node][bit];
    return node;
}

int combine(int u, int v){
    return min(u, v);
}

void dfs(int node, int par, int c){
    dep[node] = dep[par] + 1, anc[node][0] = par, cost[node][0] = c;
    for(int bit = 1; bit < 20; bit++){
        anc[node][bit] = anc[anc[node][bit - 1]][bit - 1];
        cost[node][bit] = min(cost[node][bit - 1], cost[anc[node][bit - 1]][bit - 1]);
    }
    for(auto& [new_node, value] : adj[node])
    if(new_node != par)
        dfs(new_node, node, value);
}

int lca(int u, int v){
    if(dep[u] > dep[v])
    swap(u, v);
    v = k_ancestor(v, dep[v] - dep[u]);
    if(u == v) return u;
    for(int bit = 19; bit >= 0; bit--)
    if(anc[u][bit] != anc[v][bit])
        u = anc[u][bit], v = anc[v][bit];
    return anc[u][0];
}

int get_cost(int node, int dist){
    if(dep[node] <= dist) return -1;
    int ans = OO;
    for(int bit = 0; bit < 20; bit++)
        if(dist & (1 << bit))
            ans = combine(ans, cost[node][bit]), node = anc[node][bit];
    return ans;
}

int query(int u, int v){
    if(dep[u] > dep[v])
    swap(u, v);
    int LCA = lca(u, v);
    return combine(get_cost(u, dep[u] - dep[LCA]), get_cost(v, dep[v] - dep[LCA]));
}

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