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

template < typename T = int > struct Power_Inverse {
    
    T MAX_N, mod;
    vector < T > fact, fact_inv, inv;

    T mod_combine(T a, T b, T MOD){
        return ((a % MOD) * (b % MOD)) % MOD;
    }

    T fast_power(T b, T e, T MOD){
        T power = 1;
        while(e){
            if(e & 1) power = mod_combine(power, b, MOD);
            e >>= 1, b = mod_combine(b, b, MOD);
        }
        return power % MOD;
    }

    T get_inv(T N, T MOD){
        return fast_power(N, MOD - 2, MOD) % MOD;
    }

    Power_Inverse(T N, T MOD){
        MAX_N = N, mod = MOD;
        fact.assign(MAX_N + 10, 1), inv.resize(MAX_N + 10, 1), fact_inv.resize(MAX_N + 10, 1);

        for(ll i = 1; i <= MAX_N; i++)
            fact[i] = mod_combine(fact[i - 1], i, mod);

        inv[MAX_N] = get_inv(MAX_N, mod);
        fact_inv[MAX_N] = get_inv(fact[MAX_N], mod);        
        
        for(ll i = MAX_N - 1; i >= 0; i--){
            fact_inv[i] = mod_combine(fact_inv[i + 1], i + 1, mod);
            inv[i] = mod_combine(inv[i + 1], i + 1, mod);
        }
    }

    // Combination
    T nCr(int n, int r){ // nCr = n! / (r! * (n - r)!)
        if(r > n) return 0ll;
        return mod_combine(fact[n], mod_combine(fact_inv[r], fact_inv[n - r], mod), mod);
    }

    // Permutation
    T nPr(int n, int r){ // nPr = n! / (n - r)!
        if(r > n) return 0ll;
        return mod_combine(fact[n], fact_inv[n - r], mod);
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