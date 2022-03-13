#include <bits/stdc++.h>

using namespace std;

#define cin_2d(vec, n, m) for(int i = 0; i < n; i++) for(int j = 0; j < m && cin >> vec[i][j]; j++);
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define cout_map(mp) for(auto& [f, s] : mp) cout << f << "  " << s << "\n";
#define Time cerr << "Time Taken: " << (float)clock() / CLOCKS_PER_SEC << " Secs" << "\n";
#define fixed(n) fixed << setprecision(n)
#define ceil(n, m) (((n) / (m)) + ((n) % (m) ? 1 : 0))
#define fill(vec, value) memset(vec, value, sizeof(vec));
#define Num_of_Digits(n) ((int)log10(n) + 1)
#define mod_combine(a, b, m) (((a % m) * (b % m)) % m)
#define all(vec) vec.begin(), vec.end()
#define rall(vec) vec.rbegin(), vec.rend()
#define sz(x) int(x.size())
#define debug(x) cout << #x << ": " << (x) << "\n";
#define fi first
#define se second
#define Pair pair < int, int >
#define ll long long
#define ull unsigned long long
#define Mod  1'000'000'007
#define OO 2'000'000'000
#define EPS 1e-9
#define PI acos(-1)

template < typename T = int > istream& operator >> (istream &in, vector < T > &v) {
    for (auto &x: v) in >> x;
    return in;
}

template < typename T = int > ostream& operator << (ostream &out, const vector < T > &v) { 
    for (const T &x: v) out << x << ' '; 
    return out;
}

void AhMeD_HoSSaM(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout); 
    #endif
}

struct Floyd {

    struct Edge {
        
        ll u, v, w;
        
        Edge(int U = 0, int V = 0, int W = 0){
            u = U, v = V, w = W;
        }

        bool operator < (const Edge& e) const {
            return w < e.w;
        }

    };

    int n, m;
    vector < vector < ll > > dist;
    vector < Edge > edges;

    Floyd(int N, int M){
        n = N, m = M;
        dist.assign(n + 10, vector < ll > (n + 10, 1e18));
        edges.resize(m);
    }

    ll operation(ll a, ll b, ll c){
        return min(a, b + c);
    }

    void Get_Data(){
        for(auto& e : edges){
            cin >> e.u >> e.v >> e.w;
            dist[e.u][e.u] = dist[e.v][e.v] = 0;
            dist[e.u][e.v] = dist[e.v][e.u] = min({dist[e.u][e.v], dist[e.v][e.u], e.w});
        }
    }

    void Build_Dist(){
        for(int i = 1; i <= n; i++)
            for(int u = 1; u <= n; u++)
                for(int v = 1; v <= n; v++)
                    dist[u][v] = operation(dist[u][v], dist[u][i], dist[i][v]);
    }

};

void Solve(){
    
}

int main(){
    AhMeD_HoSSaM();
    int t = 1;
    //cin >> t;
    while(t--)
        Solve();
    return 0;
}