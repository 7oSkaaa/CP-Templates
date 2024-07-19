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

template < typename T = long long , int Rounds = 10 > struct Miller_Rabin {

    T BinMul(T b, T e, T mod) {
        T res = 0;
        while (e > 0) {
            if (e & 1)
                res = ((res % mod) + (b % mod)) % mod;
            e >>= 1;
            b = ((b % mod) + (b % mod)) % mod;
        }
        return res;
    }

    T BinPow(T b, T e, T mod) {
        T res = 1;
        while (e > 0) {
            if (e & 1)
                res = BinMul(res, b, mod);
            e >>= 1;
            b = BinMul(b, b, mod);
        }
        return res;
    }

    bool is_prime(T num){ // O(Rounds * log^3(num))
        // Handling base cases:
        if(num < 2) return false;
        if(num != 2 && num % 2 == 0) return false;

        // Now our num is odd number greater than 1
        T d = num - 1;

        while (d % 2 == 0)
            d >>= 1;
        
        for (int loop = 1; loop <= Rounds; loop++) {
            T a = rand() % (num - 1) + 1, temp = d;
            T x = BinPow(a, temp, num);
            while (temp != num - 1 && x != 1 && x != num - 1) {
                x = BinMul(x, x, num);
                temp <<= 1;
            }
            if (x != num - 1 && temp % 2 == 0)
                return false;
        }
        // If we reach here, then the number is prime
        return true; 
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