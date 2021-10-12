#include <bits/stdc++.h>
using namespace std;

#define cin(vec) for(auto& i : vec) cin >> i
#define cin_2d(vec, n, m) for(int i = 0; i < n; i++) for(int j = 0; j < m && cin >> vec[i][j]; j++);
#define cout(vec) for(auto& i : vec) cout << i << " "; cout << "\n";
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define cout_map(mp) for(auto& [f, s] : mp) cout << f << "  " << s << "\n";
#define Time cerr << "Time Taken: " << (float)clock() / CLOCKS_PER_SEC << " Secs" << "\n";
#define fixed(n) fixed << setprecision(n)
#define ceil(n, m) (((n) / (m)) + ((n) % (m) ? 1 : 0))
#define fill(vec, value) memset(vec, value, sizeof(vec));
#define Num_of_Digits(n) ((int)log10(n)+1)
#define mod_combine(a, b, m) (((a % m) * (b % m)) % m)
#define all(vec) vec.begin(),vec.end()
#define rall(vec) vec.rbegin(),vec.rend()
#define sz(x) int(x.size())
#define fi first
#define se second
#define Pair pair < int, int >
#define ll long long
#define ull unsigned long long
#define Mod  1'000'000'007
#define OO 2'000'000'000
#define EPS 1e-9
#define PI acos(-1)

void AhMeD_HoSSaM(){
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
  #endif
}

constexpr int N = 3e5 + 5;

vector < int > dep(N);

vector < vector < Pair > > adj(N); 
vector < vector < int > > anc(N, vector < int > (20)), cost(N, vector < int > (20));

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

void solve(){
  int n, m, q;
  cin >> n >> m;
  for(int i = 0, u, v, w; i < m && cin >> u >> v >> w; i++)
    adj[u].push_back({v, w}), adj[v].push_back({u, w});
  cin >> q;
  int u, v;
  dfs(1, 0, OO);
  while(q-- && cin >> u >> v){
    cout << query(u, v) << "\n";
  }
}

int main(){
  AhMeD_HoSSaM();
  int t = 1;
  //cin >> t;
  while(t--)
    solve();
  Time
  return 0;
} 