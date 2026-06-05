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

/*
 * Prefix_2D — 2D Prefix Sum (static grid, rectangle sum queries)
 *
 * Template params:
 *   T = value type (default int, use ll for large sums)
 *
 * Constructor:
 *   Prefix_2D<T> ps(int N = 0, int M = 0);   // 1-indexed N×M grid
 *
 * Methods:
 *   Build_Prefix(vector<vector<T>>& matrix)      → build from 0-indexed matrix
 *   Get_Query(int x1, int y1, int x2, int y2)   → T, sum of rectangle [x1..x2]×[y1..y2]
 *   Print_Prefix()                               → print prefix table
 *
 * Example:
 *   vector<vector<int>> mat = {{1,2,3},{4,5,6},{7,8,9}};
 *   Prefix_2D<int> ps(3, 3);
 *   ps.Build_Prefix(mat);
 *   cout << ps.Get_Query(1, 1, 2, 2);  // 1+2+4+5 = 12
 *   cout << ps.Get_Query(1, 1, 3, 3);  // 45 (sum of all)
 */
template < typename T = int > struct Prefix_2D {

    int n, m;
    vector < vector < T > > prefix;
    
    Prefix_2D(int N = 0, int M = 0){
        n = N, m = M;
        prefix.assign(n + 5, vector < T > (m + 5));
    }

    // Get the sum of the number in the rectangle between x1, y1, x2, y2

    T Get_Query(int x1, int y1, int x2, int y2){
        if(x1 > x2) swap(x1, x2);
        if(y1 > y2) swap(y1, y2);
        return prefix[x2][y2] - prefix[x1 - 1][y2] - prefix[x2][y1 - 1] + prefix[x1 - 1][y1 - 1];
    }

    void Build_Prefix(vector < vector < T > >& matrix){
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                prefix[i][j] = matrix[i - 1][j - 1] + prefix[i][j - 1] + prefix[i - 1][j] - prefix[i - 1][j - 1];
    }

    void Print_Prefix(){
        for(int i = 1; i <= n; i++, cout << '\n')
            for(int j = 1; j <= m && cout << prefix[i][j] << ' '; j++);
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