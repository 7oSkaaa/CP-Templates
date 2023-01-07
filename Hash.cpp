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

template < int p = 31, int mod = 1000000009, int Mode = 0 > struct Hash {

    int n, init;
    vector < ll > p_pow, hash;                    

    void init_(){
        if(Mode == 0)
            init = 'a';
        else if(Mode == 1)
            init = 'A';
        else if(Mode == 2)
            init = '0';
        else 
            init = 0;
    }

    Hash(string const& s){
        init_();
        n = s.size();
        p_pow = hash = vector < ll > (n + 1);
        p_pow[0] = 1;
        for (int i = 1; i <= n; i++)
            p_pow[i] = (p_pow[i - 1] * p) % mod;
        for (int i = 0; i < n; i++)
            hash[i + 1] = (hash[i] + (s[i] - init + 1) * p_pow[i]) % mod;
    }

    Hash(vector < ll > const& v){
        init_();
        n = v.size();
        p_pow = hash = vector < ll > (n + 1);
        p_pow[0] = 1;
        for (int i = 1; i <= n; i++)
            p_pow[i] = (p_pow[i - 1] * p) % mod;
        for (int i = 0; i < n; i++)
            hash[i + 1] = (hash[i] + (v[i] - init + 1) * p_pow[i]) % mod;
    }

    ll sub(int l, int r){
        ll curr_hash = (hash[r] + mod - hash[l - 1]) % mod;
        return (curr_hash * p_pow[n - l]) % mod;
    }

    ll at(int idx){
        return sub(idx, idx);
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