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

/*
 * Seive_Prime_Factors — Smallest Prime Factor sieve for fast factorization
 *
 * Globals:
 *   SPF[i]          → smallest prime factor of i
 *   primeFactors[i] → vector<int>, prime factorization of i
 *
 * Functions:
 *   Seive(int N)        → build SPF[] and primeFactors[] for 1..N in O(N log log N)
 *   PrimeFactors(int x) → vector<int>, prime factors of x using SPF (O(log x))
 *
 * Usage:
 *   Call Seive(N) once at the start, then query any number ≤ N instantly.
 *
 * Example:
 *   Seive(1000000);
 *   auto pf = PrimeFactors(360);   // {2, 2, 2, 3, 3, 5}
 *   // or use precomputed:
 *   auto& pf2 = primeFactors[360]; // same result
 *   cout << SPF[360];              // 2
 */

// Vector to store smallest prime factor of numbers from 1 to N.
vector < int > SPF;

// Vector to store prime factors of numbers from 1 to N.
vector < vector < int > > primeFactors;

// Function to calculate prime factors of a number.
vector < int > PrimeFactors(int x){
    vector < int > ret;
    while(x > 1){
        ret.push_back(SPF[x]);
        x /= SPF[x];
    }
    return ret;
}

// Function to calculate smallest prime factors of numbers from 1 to N using Sieve of Eratosthenes.
void Seive(int N){
    // Initializing vector SPF to store smallest prime factor of numbers from 1 to N.
    SPF = vector < int > (N + 5);

    // Initializing vector primeFactors to store prime factors of numbers from 1 to N.
    primeFactors = vector < vector < int > > (N + 5);

    // Initializing SPF vector with i for all numbers.
    for(int i = 1; i <= N; i++)
        SPF[i] = i;

    // Updating SPF vector for even numbers.
    for(int i = 2; i <= N; i += 2)
        SPF[i] = 2;

    // Updating SPF vector for odd numbers.
    for(int i = 3; i * i <= N; i++){
        if(SPF[i] == i){
            for(int j = i * i; j <= N; j += i)
                if(SPF[j] == j)
                    SPF[j] = i;
        }
    }

    // Calculating prime factors of numbers from 1 to N.
    for(int i = 1; i <= N; i++)
        primeFactors[i] = PrimeFactors(i);
}

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