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

template < typename T = long long , int Base = 0 > struct Hash {
    
    int n;
    vector < T > pow1, pow2, h1, h2;
    const T p1 = 313, p2 = 1013;
    const T m1 = 1e9 + 7, m2 = 1e9 + 9;
 
    Hash(const string& s){
        n = s.size();
        h1 = h2 = pow1 = pow2 = vector < T > (n + 5);

        // calulcate the powers
        pow1[0] = pow2[0] = 1;
        for(int i = 1; i <= n; i++) {
            pow1[i] = (pow1[i - 1] * p1) % m1;
            pow2[i] = (pow2[i - 1] * p2) % m2;
        }

        // calculate the hashes
        h1[0] = h2[0] = 1;
        for(int i = 1; i <= n; i++) {
            h1[i] = (h1[i - 1] * p1 + s[i - !Base]) % m1;
            h2[i] = (h2[i - 1] * p2 + s[i - !Base]) % m2;
        }
    }

    Hash(const vector < T >& vec){
        n = vec.size();
        h1 = h2 = pow1 = pow2 = vector < T > (n + 5);
        
        // calulcate the powers
        pow1[0] = pow2[0] = 1;
        for(int i = 1; i <= n; i++) {
            pow1[i] = (pow1[i - 1] * p1) % m1;
            pow2[i] = (pow2[i - 1] * p2) % m2;
        }

        // calculate the hashes
        h1[0] = h2[0] = 1;
        for(int i = 1; i <= n; i++) {
            h1[i] = (h1[i - 1] * p1 + vec[i - !Base]) % m1;
            h2[i] = (h2[i - 1] * p2 + vec[i - !Base]) % m2;
        }
    }

    // get the hash of substring [i, j]
    pair < T, T > sub(int l, int r) {
        // first hash
        T F = h1[r];
        F -= h1[l - 1] * pow1[r - l + 1];
        F = ((F % m1) + m1) % m1;
        
        // second hash
        T S = h2[r];
        S -= h2[l - 1] * pow2[r - l + 1];
        S = ((S % m2) + m2) % m2;
        
        return {F, S};
    }
 
    // merge two substrings
    pair < T, T > merge_hash(int l1, int r1, int l2, int r2) {
        auto a = sub(l1, r1), b = sub(l2, r2);
        ll F = ((a.first * pow1[r2 - l2 + 1]) + b.first) % m1;
        ll S = ((a.second * pow2[r2 - l2 + 1]) + b.second) % m2;
        return {F, S};
    }
 
    // get the hash of the idx'th character
    pair < T, T > at(int idx){
        return sub(idx, idx);
    }

    // check if two parts are equals
    bool equal(int l1, int r1, int l2, int r2) {
        return sub(l1, r1) == sub(l2, r2);
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