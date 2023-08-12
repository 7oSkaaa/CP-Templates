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

template < typename T = int > struct Prim {

    struct Edge {

        T v, w;

        Edge(T V = 0, T W = 0) : v(V), w(W) {}

        bool operator < (const Edge &e) const {
            return w < e.w;
        }

    };

    vector < vector < Edge > > adj;
    vector < T > marked;

    Prim(int n = 0){
        adj = vector < vector < Edge > > (n + 10);
        marked = vector < T > (n + 10, 0);
    }

    void build_adj(int edges, bool is_directed = false){
        for(int i = 0, u, v, w; i < edges && cin >> u >> v >> w; i++){
            adj[u].push_back(Edge(v, w));
            if(!is_directed)
                adj[v].push_back(Edge(u, w));
        }
    }

    T get_cost(int root){
        T cost = 0;
        priority_queue < Edge > pq;
        pq.push(Edge(root, 0));
        while(!pq.empty()){
            auto [u, curr_cost] = pq.top();
            pq.pop();
            // Checking for cycle
            if(marked[u]) continue;
            marked[u] = true;
            cost += curr_cost;
            for(auto& [v, w] : adj[u]){
                if(!marked[v])
                    pq.push(Edge(v, w));
            }
        }
        return cost;
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