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

class Tarjan {
public:
    Tarjan(int n) {
        init(n);
    }

    void addEdge(int u, int v, bool is_directed = false) {
        adj[u].push_back(v);
        if (!is_directed)
            adj[v].push_back(u); // Assuming an undirected graph
    }

    void run() {
        for (int i = 0; i < adj.size(); ++i) {
            if (node_idx[i] == -1) {
                dfs(i);
            }
        }
    }
    
    set < int > getArticulationPoints() {
        return art_points;
    }

    vector < pair < int, int > > getBridges() {
        return bridges;
    }

    bool isArticulationPoint(int u) {
        return art_points.find(u) != art_points.end();
    }

    bool isBridge(int u, int v) {
        return find(bridges.begin(), bridges.end(), make_pair(u, v)) != bridges.end() ||
               find(bridges.begin(), bridges.end(), make_pair(v, u)) != bridges.end();
    }

    vector < vector < int > > getComponents() {
        return comps;
    }

private:
    int timer;
    vector < vector < int > > adj, comps;
    vector < int > low_link, node_idx, comp_idx;
    vector < bool > in_stack;
    stack < int > stk;
    vector < pair < int, int > > bridges;
    set < int > art_points;

    void init(int n) {
        timer = 0;
        adj.assign(n + 5, vector < int > ());
        low_link.assign(n + 5, -1);
        node_idx.assign(n + 5, -1);
        comp_idx.assign(n + 5, -1);
        in_stack.assign(n + 5, false);
        comps.clear();
        while (!stk.empty()) stk.pop();
    }

    void dfs(int u, int parent = -1) {
        low_link[u] = node_idx[u] = timer++;
        in_stack[u] = true;
        stk.push(u);

        int childs = 0;

        for (int v : adj[u]) {
            if (v == parent) continue; // Ignore the edge to parent in undirected graph
            if (node_idx[v] == -1) { // If v is not visited
                dfs(v, u);
                low_link[u] = min(low_link[u], low_link[v]);
                if (low_link[v] == node_idx[v])
                    bridges.emplace_back(u, v);
                if (parent != -1 && low_link[v] >= node_idx[u])
                    art_points.insert(u);
                ++childs;
            } else if (in_stack[v]) {
                low_link[u] = min(low_link[u], node_idx[v]);
            }
        }

        if (parent == -1 && childs > 1)
            art_points.insert(u);

        if (low_link[u] == node_idx[u]) {
            comps.emplace_back();
            int v;
            do {
                v = stk.top();
                stk.pop();
                in_stack[v] = false;
                comps.back().push_back(v);
                comp_idx[v] = comps.size() - 1;
            } while (v != u);
        }
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