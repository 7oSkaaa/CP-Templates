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

int timer;
vector < vector < int > > adj, comps;
vector < int > low_link, in_stack, node_idx, comp_idx;
stack < int > stk;
vector < Pair < int > > bridges;
set < int > art_points;

void init(int n){
    timer = 0;
    adj = vector < vector < int > > (n + 5);
    low_link = node_idx = comp_idx = vector < int > (n + 5, -1);
    in_stack = vector < int > (n + 5, false);
    comps.clear();
    stk = stack < int > ();
}

void tarjan(int u){
    in_stack[u] = true;
    low_link[u] = node_idx[u] = timer++;
    stk.push(u);
    for(auto& v : adj[u]){
        if(node_idx[v] == -1){
            tarjan(v);
            // minimize ancestor of my child
            low_link[u] = min(low_link[u], low_link[v]);
            // add bridge
            if(low_link[v] == node_idx[v])
                bridges.push_back({u, v});
            // add articulation point
            if(low_link[v] >= node_idx[u])
                art_points.insert(u);
        }else if(in_stack[v])
            low_link[u] = min(low_link[u], node_idx[v]);
    }

    // head of SCC
    if(low_link[u] == node_idx[u]){
        comps.push_back(vector < int > ());
        int v = -1;
        while(v != u){
            v = stk.top();
            stk.pop();
            in_stack[v] = false; // remove from stack
            comps.back().push_back(v); // add node to current component
            comp_idx[v] = sz(comps) - 1; // set component index
        }
    }
}

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