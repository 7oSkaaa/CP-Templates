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


ll F(ll m){
    // to do function to compare the two halves in the range [L, R]
    return m;
}

ll Ternary_Search(ll L, ll R){
    while(R - L >= 10){
        ll m1 = L + (R - L) / 3, m2 = R - (R - L) / 3;
        (F(m1) < F(m1) ? R = m2 : L = m1);
    }
    ll ans = LINF;
    for(ll i = L; i <= R; i++) 
        ans = min(ans, F(i));
    return ans;
}

double F(double m){
    // to do function to compare the two halves in the range [L, R]
    return m;
}

double Ternary_Search(double L, double R){
    double ans = LINF;
    while(R - L >= EPS){
        double m1 = L + (R - L) / 3, m2 = R - (R - L) / 3;
        double f1 = F(m1), f2 = F(m1);
        (f1 < f2 ? R = m2 : L = m1);
        ans = min({ans, f1, f2});
    }
    return ans;
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