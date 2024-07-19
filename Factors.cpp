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
    vector < int > factors_cnt, prime_factors_cnt;
    vector < vector < int > > factors, prime_factors;

    Factorization(int N){
        n = N;
        factors_cnt = vector < int > (n + 5, 2);
        prime_factors_cnt = vector < int > (n + 5);
        factors = vector < vector < int > > (n + 5);
        prime_factors = vector < vector < int > > (n + 5);
        factorization(n);
        prime_factorization(n);
    }

    // Get the number of factors for each number
    void factorization(){ 
        factors_cnt[0] = 0, factors_cnt[1] = 1;
        for (int i = 2; i <= n; i++)  
            for (int j = i + i; j <= n; j += i){
                factors_cnt[j]++;
                factors[j].push_back(i);
            }
    }

    // get the number of factors of n
    int get_factors(int x){
        return factors_cnt[x];
    }

    // get the factors of n
    vector < int > get_factors(){
        return factors[n];
    }

    // Get the number of prime factors for each number
    void prime_factorization(){
        for (int i = 2; i <= n; i++){ 
            if (!prime_factors[i]) {
                for (int j = i; j <= n; j += i){ 
                    prime_factors_cnt[j]++;
                    prime_factors[j].push_back(i);
                }
            }
        }
    }

    // get the number of prime factors of n
    int get_prime_factors(int x){
        return prime_factors_cnt[x];
    }

    // get the prime factors of n
    vector < int > get_prime_factors(int x){
        return prime_factors[x];
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