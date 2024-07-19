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

template < typename T = int >
class LCA {
public:
    LCA(
        int n,
        const vector < vector < pair< int, T > > >& adj_list, 
        const function < T(const T&, const T&) > op = [](const T& a, const T& b) { return a + b; },
        const T def = T()
    ) : N(n), adj(adj_list), operation(op), default_value(def) {
        LOG = 1;
        while ((1 << LOG) <= N) LOG++;
        dep = vector < int > (N + 5, -1);
        anc = vector < vector < int > > (N + 5, vector < int > (LOG));
        cost = vector < vector < T > > (N + 5, vector < T > (LOG, default_value));
        build();
    }

    void build() {
        for (int i = 1; i <= N; ++i)
            if (dep[i] == -1) {
                dep[i] = 0;  // Initialize root node's depth to 0
                dfs(i);
            }
    }

    int get_lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        u = kth_ancestor(u, dep[u] - dep[v]);
        if (u == v) return u;
        for (int bit = LOG - 1; bit >= 0; bit--)
            if (anc[u][bit] != anc[v][bit])
                u = anc[u][bit], v = anc[v][bit];
        return anc[u][0];
    }

    T query(int u, int v) {
        int lca = get_lca(u, v);
        return operation(get_cost(u, dep[u] - dep[lca]), get_cost(v, dep[v] - dep[lca]));
    }

private:
    int N, LOG;
    vector < vector < int > > anc;
    vector < vector < T > > cost;
    vector < vector < pair < int, T > > > adj;
    vector < int > dep;
    const function < T(const T&, const T&) > operation;
    const T default_value;

    void dfs(int u, int p = 0) {
        for (auto& [v, w] : adj[u]) {
            if (v == p) continue;
            if (dep[v] == -1) {
                dep[v] = dep[u] + 1, anc[v][0] = u, cost[v][0] = w;
                for (int bit = 1; bit < LOG; bit++) {
                    anc[v][bit] = anc[anc[v][bit - 1]][bit - 1];
                    cost[v][bit] = operation(cost[v][bit - 1], cost[anc[v][bit - 1]][bit - 1]);
                }
                dfs(v, u);
            }
        }
    }

    int kth_ancestor(int u, int k) {
        if (dep[u] < k) return -1;
        for (int bit = LOG - 1; bit >= 0; bit--)
            if (k & (1 << bit))
                u = anc[u][bit];
        return u;
    }

    T get_cost(int u, int dist) {
        if (dep[u] < dist) return -1;
        T ans = default_value;
        for (int bit = 0; bit < LOG; bit++)
            if (dist & (1 << bit))
                ans = operation(ans, cost[u][bit]), u = anc[u][bit];
        return ans;
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