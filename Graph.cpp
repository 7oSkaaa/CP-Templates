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

struct Graph {

    int n, m, connected_components;
    vector < vector < int > > adj;
    vector < bool > vis;
    vector < int > depth, parent, deg, colour;
    
    Graph(int N, int M){
        n = N, m = M;
        connected_components = 0;
        adj = vector < vector < int > > (n + 10);
        vis = vector < bool > (n + 10, false);
        depth = deg = colour = vector < int > (n + 10, 0);
        parent = vector < int > (n + 10, -1);
    }

    void add_edge(int u, int v, bool is_directed = false){
        adj[u].push_back(v), deg[u]++; 
        if(!is_directed) 
            adj[v].push_back(u), deg[v]++;
    }

    void remove_edge(int u, int v){
        adj[u].erase(find(all(adj[u]), v)), adj[v].erase(find(all(adj[v]), u));
    }

    void build_adj(bool is_directed = false){
        for(int i = 0, u, v; i < m && cin >> u >> v; i++)
            add_edge(u, v, is_directed);
    }

    void dfs(int node, int dep = 0, int par = -1){
        vis[node] = true, parent[node] = par, depth[node] = dep;
        for(auto& new_node : adj[node])
            if(!vis[new_node])
                dfs(new_node, dep + 1, node);
    }

    bool is_cycle(int node, int par){
        vis[node] = true;
        for(auto& new_node : adj[node]){
            if(!vis[new_node]){
                if(is_cycle(new_node, node))
                    return true;
            }
            else if(new_node != par)
                return true;
        }
        return false;
    }

    void get_path(int node){
        if(parent[node] == node) return;
        cout << node << " ";
        get_path(parent[node]);
    }

    void topology (){
        queue < int > topo;
        vector < int > graph;
        for(int i = 1; i <= n; i++)
            if(deg[i] == 1) topo.push(i), deg[i]--;
        while(!topo.empty()){
            int curr_node = topo.front();
            topo.pop();
            graph.push_back(curr_node);
            for(auto& new_node : adj[curr_node]){
                deg[new_node]--;
                if(deg[new_node] == 1)
                    topo.push(new_node);
            }
        }
        reverse(all(graph));
        cout << graph << "\n";
    }

    int bfs(int from, int to){
        if(from == to) return 0;
        queue < int > BFS;
        depth.assign(n + 10, OO);
        vis[from] = true, depth[from] = 0;
        BFS.push(from);
        while(!BFS.empty()){
            int sz = sz(BFS);
            while(sz--){
                int curr_node = BFS.front();
                BFS.pop();
                for(auto& new_node : adj[curr_node]){
                    if(!vis[new_node]){
                        BFS.push(new_node), parent[new_node] = curr_node; 
                        depth[new_node] = min(depth[new_node], depth[curr_node] + 1);
                        vis[new_node] = true;
                    }
                }
            }
        }
        return depth[to];
    }

    bool is_Bipartite(int u){
        for(auto v : adj[u]){
            if(colour[v] == colour[u])
                return false;
            else if(colour[v] == 0){
                colour[v] = -colour[u];
                if(!is_Bipartite(v)){
                    return false;
                }
            }
        }
        return true;
    }
    
    bool is_Bipartite(){
        for(int i = 1; i <= n; i++){
            if(colour[i] == 0) {
                colour[i] = -1;
                if(!is_Bipartite(i))
                    return false;
            }
        }
        return true;
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