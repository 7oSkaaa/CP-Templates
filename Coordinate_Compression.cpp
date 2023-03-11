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

template < typename T = int > struct Coordinate_Compression {

    vector < T > compressed;
    bool is_build = true;

    Coordinate_Compression(){}

    Coordinate_Compression(vector < T > &vec) {
        compressed = vec;
        build();
    }

    void add(T x) {
        compressed.push_back(x);
        is_build = false;
    }

    void build() {
        sort(all(compressed));
        compressed.resize(unique(all(compressed)) - compressed.begin());
        is_build = true;
    }

    T get(T x) {
        if(!is_build) build();
        return upper_bound(all(compressed), x) - compressed.begin();
    }

    vector < T > get_compressed(vector < T > &vec) {
        if(!is_build) build();
        vector < T > ret;
        for (auto &x : vec) 
            ret.push_back(get(x));
        return ret;
    }

    vector < T > get_mapping(vector < T > &vec) {
        if(!is_build) build();
        vector < T > ret(sz(compressed) + 5);
        for (auto &x : vec)
            ret[get(x)] = x;
        return ret;
    }

    int size(){
        if(!is_build) build();
        return sz(compressed);
    }

};

void Solve(){
    
}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--)
        Solve();
    return 0;
}