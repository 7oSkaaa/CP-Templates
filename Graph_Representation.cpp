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

/*
 * Graph_Representation — Linked-list (head array) adjacency representation
 *
 * Faster cache-friendly alternative to vector<vector<Edge>> for dense graphs.
 *
 * Setup:
 *   init(int n, int m);         // n nodes, m edges (allocates 2*m+5 edge slots)
 *   addEdge(int u, int v, int c = 0);     // directed edge u→v with cost c
 *   AddBiEdge(int u, int v, int c = 0);   // undirected: both directions
 *
 * Traversal macro:
 *   adj_loop(u, v, e)
 *   // Iterates over all neighbors v of u, e = edge index
 *   // edges[e].cost = edge weight
 *
 * Example:
 *   init(n, m);
 *   for(int i = 0; i < m; i++) {
 *       int u, v, w; cin >> u >> v >> w;
 *       AddBiEdge(u, v, w);
 *   }
 *   // Traverse neighbors of node 1:
 *   adj_loop(1, v, e) {
 *       cout << v << " " << edges[e].cost << "\n";
 *   }
 */

// ----------------------------------------------------------- //

#define adj_loop(u, v, e) for(int e = head[u], v; ~e && (v = edges[e].to, 1); e = edges[e].nxt)

template < typename T = int > struct edgeData {

    T to, nxt, cost;

    edgeData(T TO = 0, T NXT = 0, T COST = 0) : to(TO), nxt(NXT), cost(COST) {}

};

int edge_count;
vector < edgeData < int > > edges;
vector < int > head;

void init(int n, int m){
    edges = vector < edgeData < int > > (2 * m + 5);
    head = vector < int > (n + 5, -1);
    edge_count = 1;
}

void addEdge(int u, int v, int c = 0){
    edges[edge_count].to = v;
    edges[edge_count].cost = c;
    edges[edge_count].nxt = head[u];
    head[u] = edge_count++;
}

void AddBiEdge(int u, int v, int c = 0){
    addEdge(u, v, c);
    addEdge(v, u, c);
}

// ----------------------------------------------------------- //


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