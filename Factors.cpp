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

struct Factorization {
    
    int n;
    vector < int > factors;
    vector < int > prime_factors;

    Factorization(int N){
        n = N;
        factors.assign(n + 10, 2);
        prime_factors.resize(n + 10);
    }

    // Get the number of factors for each number

    void factorization(int n){ 
        for (ll i = 2; i <= n; i++) {  
            for (ll j = i * 2; j <= n; j += i) factors[j]++;
        }
    }

    ll get_factors(ll n){
        return factors[n];
    }

    // Get the number of prime factors for each number

    void prime_factorization(int n){
        for (ll i = 2; i <= n; i++){ 
            if (!prime_factors[i]) { 
                for (ll j = 2 * i; j <= n; j += i) prime_factors[j]++;
                prime_factors[i] = 1; 
            }
        }
    }

    ll get_prime_factors(ll n){
        return prime_factors[n];
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