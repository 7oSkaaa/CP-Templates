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
 * Seive — Sieve of Eratosthenes for primality testing
 *
 * Template params:
 *   T = integer type (default int)
 *
 * Constructor:
 *   Seive<T> s(int n);
 *   // Builds is_prime[] for 0..n in O(n log log n)
 *
 * Methods:
 *   get_primes(int n)   → fills primes[] vector with all primes ≤ n
 *   print_primes()      → print all primes in primes[]
 *
 * Members:
 *   is_prime[i]   → bool, true if i is prime
 *   primes        → vector<T>, filled after calling get_primes()
 *
 * Example:
 *   Seive<int> s(100);
 *   cout << s.is_prime[97];  // 1
 *   cout << s.is_prime[100]; // 0
 *   s.get_primes(100);
 *   s.print_primes();        // 2 3 5 7 11 ... 97
 */
template < typename T = int > struct Seive {

    vector < bool > is_prime;
    vector < T > primes;

    Seive(int n){
        is_prime.assign(n + 1, true);
        is_prime[0] = is_prime[1] = false;
        for(ll i = 2; i <= sqrt(n); i++)
            if(is_prime[i])
                for(ll j = i * i; j <= n; j += i) is_prime[j] = false;
    }

    // Build vector with prime numbers

    void get_primes(int n){
        for(int i = 1; i <= n; i++)
            if(is_prime[i])
                primes.push_back(i);
    }

    // Print the prime numbers

    void print_primes(){
        for(auto& p : primes)
            cout << p << " ";
        cout << "\n";
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