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

template < typename T = int > struct Centroid_Decomposition {

    int n, treeRoot;
    const vector < vector < T > > adj;
    vector < T > SubtreeSz, isCentroid;

    // Initialize the Centroid Decomposition
    Centroid_Decomposition(int N, const vector <vector < T > > &G, int Root = 1) : adj(G){
        n = N, treeRoot = Root;
        SubtreeSz = isCentroid = vector < T > (n + 5, 0);
    }

    // update subtree size of each node
    int updateSize(int u, int p = -1){
        SubtreeSz[u] = 1;
        for (int v : adj[u]) 
            if (v != p && !isCentroid[v]) 
                SubtreeSz[u] += updateSize(v, u);
        return SubtreeSz[u];
    }

    // get centroid of subtree rooted at u
    int getCentroid(int u, int target, int p = -1){
        for(auto& v : adj[u]){
            if(v == p || isCentroid[v]) continue;
            if(SubtreeSz[v] * 2 > target) 
                return getCentroid(v, target, u);
        }
        return u;
    }

    // decompose tree into centroid tree
    void Centroid(int u, int p = 0){
        int centroidPoint = getCentroid(u, updateSize(u));
        
        // do something with centroid

        isCentroid[centroidPoint] = true;
        for(auto& v : adj[centroidPoint]){
            if(isCentroid[v]) continue;
            Centroid(v, centroidPoint);
        }
    }
    
    // call this function to decompose the tree
    void Decompose(){
        Centroid(treeRoot);
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