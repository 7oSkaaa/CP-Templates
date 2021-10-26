#include <bits/stdc++.h>
using namespace std;
 
#define cin(vec) for(auto& i : vec) cin >> i
#define cin_2d(vec, n, m) for(int i = 0; i < n; i++) for(int j = 0; j < m && cin >> vec[i][j]; j++);
#define cout(vec) for(auto& i : vec) cout << i << " "; cout << "\n";
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define cout_map(mp) for(auto& [f, s] : mp) cout << f << "  " << s << "\n";
#define Time cerr << "Time Taken: " << (float)clock() / CLOCKS_PER_SEC << " Secs" << "\n";
#define fixed(n) fixed << setprecision(n)
#define ceil(n, m) (((n) / (m)) + ((n) % (m) ? 1 : 0))
#define fill(vec, value) memset(vec, value, sizeof(vec));
#define Num_of_Digits(n) ((int)log10(n)+1)
#define mod_combine(a, b, m) (((a % m) * (b % m)) % m)
#define all(vec) vec.begin(),vec.end()
#define rall(vec) vec.rbegin(),vec.rend()
#define sz(x) int(x.size())
#define TC int t; cin >> t;   while(t--)
#define fi first
#define se second
#define Pair pair < int, int >
#define ll long long
#define ull unsigned long long
#define Mod  1'000'000'007
#define OO 2'000'000'000
#define EPS 1e-9
#define PI acos(-1)
 
void AhMeD_HoSSaM(){
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
  #endif
} 

ll fast_pow(ll b, ll e, ll mod){
    ll power = 1;
    while(e){
        if(e & 1) power = ((power % mod) * (b % mod)) % mod;
        e >>= 1;
        b = ((b % mod) * (b % mod)) % mod;
    }
    return power % mod;
}

vector < ll > factorial(1e5 + 1, 1);

ll mod_inverse(ll n, ll p){
  return fast_pow(n, p - 2, p);
}

void fact(){
  for(int i = 1; i <= 1e5; i++) factorial[i] = mod_combine(factorial[i - 1], i, Mod);
}

ll nCr(ll n, ll r){
  if(n < r) return 0;
  if(r == 0) return 1;
  return ((factorial[n] * mod_inverse(factorial[r], Mod)) % Mod * mod_inverse(factorial[n - r], Mod) % Mod) % Mod;
}

int main(){
  AhMeD_HoSSaM();
  fact();
  TC {
    ll a, b;
    cin >> a >> b;
    if(a <= b) cout << 0 << "\n";
    else 
      cout << mod_combine(2ll, nCr(a - 1, b), Mod) << "\n";   
  }
  Time
  return 0;
} 