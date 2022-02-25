#include <bits/stdc++.h>

using namespace std;

#define cin_2d(vec, n, m) for(int i = 0; i < n; i++) for(int j = 0; j < m && cin >> vec[i][j]; j++);
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

struct Dijkstra {
    
    struct Edge {
        int to, from, w;
        Edge(int from, int to, int w): from(from), to(to), w(w) {}
        bool operator < (const Edge& e) const {
            return w > e.w;
        }
    };

    vector < vector < Edge > > adj;

    Dijkstra(int edges){
        adj.resize(edges);
    }

    int Min_Cost(int search, int dest = -1){
        int n = sz(adj);
        vector < int > dist(n, OO), prev(n, -1);
        dist[search] = 0;
        priority_queue < Edge > Dij;
        Dij.push(Edge(-1, 0, 0));
        while(!Dij.empty()){
            Edge e = Dij.top();
            Dij.pop();
            if(e.w > dist[e.to]) continue;
            prev[e.to] = e.from;
            for(auto& edge: adj[e.to]){
                if(dist[edge.to] > dist[edge.from] + edge.w){
                    edge.w = dist[edge.to] = dist[edge.from] + edge.w;
                    Dij.push(edge);
                }
            }
        }
        return (dest == -1 ? -1 : dist[dest]);
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