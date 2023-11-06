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

template < typename T = int , int Base = 1 > struct Kuhn {
    int n, m;
    vector < vector < T > > adj;
    vector < T > matching, vis;
 
    Kuhn(int N, int M, const vector < vector < T > >&G) : n(N), m(M), adj(G) {
        matching = vector < T > (m + 5, -1);
        vis = vector < T > (n + 5, 0);
    }
 
    bool match(int u, int& cur){
        if(vis[u] == cur) return false;
        vis[u] = cur;
        for(auto& v: adj[u])
            if(matching[v] == -1 || match(matching[v], cur))
                return matching[v] = u, true;
        return false;
    }
 
    T max_match(){
        T cur = 1;
        for(int i = Base; i < n + Base; i++, cur++)
            match(i, cur);
        T ans = 0;
        for(int i = Base; i < m + Base; i++) 
            ans += (matching[i] != -1);
        return ans;
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