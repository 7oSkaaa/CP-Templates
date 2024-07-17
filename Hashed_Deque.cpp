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

template < typename T >
class Hashed_Deque {
private:
    int len;
    vector < ll > val;
    deque < T > curr;

    static mt19937 rng; // Declaration of static member
    static vector < ll > mod;

    // N is the largest size of the container
    // base is the minimum prime number larger than the maximum value of the container
    const int N = 500005;
    const ll base = 1000000007;

    vector < vector < ll > > p, inv;

    // Check if a number is prime
    static bool is_prime(ll x) {
        if (x < 2 || (x % 2 == 0 && x != 2)) return false;
        for (ll i = 3; i * i <= x; i += 2) {
            if (x % i == 0) return false;
        }
        return true;
    }

    // Find the next prime number greater than x
    static ll nxt_prime(ll x) {
        while (!is_prime(x)) ++x;
        return x;
    }

    // Initialize mod values using static once_flag
    static void get_mods() {
        static once_flag flag;
        call_once(flag, []() {
            mt19937 local_rng(chrono::steady_clock::now().time_since_epoch().count());
            mod.resize(2);
            mod[0] = nxt_prime(uniform_int_distribution < ll >(900000000, 1000000009)(local_rng));
            mod[1] = nxt_prime(uniform_int_distribution < ll >(900000000, 1000000009)(local_rng));
            while (mod[1] == mod[0])
                mod[1] = nxt_prime(uniform_int_distribution < ll >(900000000, 1000000009)(local_rng));
        });
    }

    // Fast exponentiation modulo m
    ll fast_power(ll base_val, ll exp, ll mod_val) {
        ll res = 1;
        while (exp > 0) {
            if (exp % 2 == 1)
                res = (res * base_val) % mod_val;
            base_val = (base_val * base_val) % mod_val;
            exp /= 2;
        }
        return res;
    }

    void initial() {
        p = inv = vector < vector < ll > >(N, vector < ll > (2, 1));
        get_mods();
        for (int i = 1; i < N; ++i) {
            for (int j = 0; j < 2; ++j) {
                p[i][j] = (p[i - 1][j] * base) % mod[j];
                inv[i][j] = fast_power(p[i][j], mod[j] - 2, mod[j]);
            }
        }
    }

public:
    Hashed_Deque() : len(0), val(2, 0) {
        initial();
    }

    // Generate random number in range [l, r]
    ll rand(ll l, ll r) {
        return uniform_int_distribution < ll > (l, r)(rng);
    }

    void push_back(T x) {
        for (int i = 0; i < 2; ++i)
            val[i] = ((val[i] * base) % mod[i] + x) % mod[i];
        curr.push_back(x);
        ++len;
    }

    void push_front(T x) {
        for (int i = 0; i < 2; ++i)
            val[i] = ((x * p[len][i]) % mod[i] + val[i]) % mod[i];
        curr.push_front(x);
        ++len;
    }

    void pop_back() {
        for (int i = 0; i < 2; ++i) {
            val[i] = ((val[i] - curr.back()) % mod[i] + mod[i]) % mod[i];
            val[i] = (val[i] * inv[1][i]) % mod[i];
        }
        curr.pop_back();
        --len;
    }

    void pop_front() {
        --len;
        for (int i = 0; i < 2; ++i) {
            ll v = (1ll * curr.front() * p[len][i]) % mod[i];
            val[i] = ((val[i] - v) % mod[i] + mod[i]) % mod[i];
        }
        curr.pop_front();
    }

    int size() const {
        return len;
    }

    bool operator == (const Hashed_Deque < T >& rhs) const {
        return len == rhs.len && val == rhs.val;
    }
};
// Definition of static members outside the class definition
template < typename T > mt19937 Hashed_Deque < T >::rng(chrono::steady_clock::now().time_since_epoch().count());
template < typename T > vector < ll > Hashed_Deque < T >::mod;

void Solve(){
    
}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--)
        Solve();
    return 0;
}