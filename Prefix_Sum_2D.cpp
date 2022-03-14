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

struct Prefix_2D {

    int n, m;
    vector < vector < ll > > prefix;
    
    Prefix_2D(int N, int M){
        n = N, m = M;
        prefix.assign(n + 5, vector < ll > (m + 5));
    }

    void Get_Data(){
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                cin >> prefix[i][j];
    }

    // Get the sum of the number in the rectangle between x1, y1, x2, y2

    ll Get_Query(int x1, int y1, int x2, int y2){
        if(x1 > x2) swap(x1, x2);
        if(y1 > y2) swap(y1, y2);
        return prefix[x2][y2] - prefix[x1 - 1][y2] - prefix[x2][y1 - 1] + prefix[x1 - 1][y1 - 1];
    }

    void Build_Prefix(){
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                prefix[i][j] += prefix[i][j - 1];
        for(int j = 1; j <= m; j++)
            for(int i = 1; i <= n; i++)
                prefix[i][j] += prefix[i - 1][j];
    }

    void Print_Prefix(){
        for(int i = 1; i <= n; i++, cout << '\n')
            for(int j = 1; j <= m && cout << prefix[i][j] << ' '; j++);
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