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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Hashed_Deque {

    int len;
    vector < int > val; 
    deque < int > curr;
    // N is the larget size of the container
    // base is the minimum prime number larger than the maximum value of the container
    const int N = 5e5 + 5, base = 1e9 + 7;

    Hashed_Deque(){
        val = vector < int > (2);
        curr.clear();
        len = 0;
        initial();
    }

    ll rand(ll l, ll r){
        return uniform_int_distribution < ll >(l, r)(rng);
    }

    vector < ll > mod;
    vector < vector < ll > > p, inv;

    bool is_prime(ll x){
        if(x < 2 || (x % 2 == 0 && x != 2)) return false;
        for(int i = 3; i <= sqrt(x); i += 2)
            if(x % i == 0) 
                return false;
        return true;
    }

    ll nxt_prime(ll x){
        while(!is_prime(x)) x++;
        return x;
    }

    void get_mods(){
        mod[0] = nxt_prime(rand(9e8, 1e9 + 9));
        mod[1] = nxt_prime(rand(9e8, 1e9 + 9));
        while(mod[1] == mod[0])
            mod[1] = nxt_prime(rand(9e8, 1e9 + 9));
    }

    ll fast_power(ll b, ll md){
        ll e = md - 2, res = 1;
        while(e) {
            if(e & 1)
                res = ((res % md) * (b % md)) % md;
            b = ((b % md) * (b % md)) % md;
            e >>= 1;
        }
        return res;
    }

    void initial(){
        mod = vector < ll > (2);
        p = inv = vector < vector < ll > > (N, vector < ll > (2, 1));
        get_mods();
        for(int i = 1; i < N;++i) 
            for(int j = 0;j < 2; ++j){
                p[i][j] = 1ll * p[i - 1][j] * base % mod[j];
                inv[i][j] = fast_power(p[i][j], mod[j]);
            }
    }

    void push_back(int x){
        for(int i = 0; i < 2; ++i)
            val[i] = (1ll * val[i] * base % mod[i] + x) % mod[i];
        curr.push_back(x);
        ++len;
    }

    void push_front(int x){
        for(int i = 0; i < 2;++i)
        val[i] = (1ll * x * p[len][i] % mod[i] + val[i]) % mod[i];
        curr.push_front(x);
        ++len;
    }

    void pop_back(){
        for(int i = 0; i < 2; ++i){
            val[i] = ((val[i] - curr.back()) % mod[i] +mod[i]) %mod[i];
            val[i] = 1ll * val[i] * inv[1][i] % mod[i];
        }
        curr.pop_back();
        --len;
    }

    void pop_front(){
        --len ;
        for(int i = 0; i < 2; ++i){
            int v = 1ll * curr.front() * p[len][i] % mod[i];
            val[i] = ((val[i] - v) % mod[i] + mod[i]) % mod[i];
        }
        curr.pop_front();
    }

    int size(){
        return len;
    }

    bool operator ==(const Hashed_Deque &rhs){
        return (rhs.len == len) && (rhs.val[0] == val[0]) && (rhs.val[1] == val[1]);
    }

};

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