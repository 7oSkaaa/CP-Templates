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
#define mod_combine(a, b, m) (((a % m) + (b % m)) % m)
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

vector < vector < ll > > prefix;
vector < vector < ll > > partial;
  

ll sum_range(int i, int j, int k, int l, vector < vector < ll > >& prefix){
  return prefix[k][l] - prefix[i - 1][l] - prefix[k][j - 1] + prefix[i - 1][j - 1];
}

void build_prefix(int n, int m){
  prefix.assign(n + 5, vector < ll > (m + 5));
  for(int i = 1; i < n; i++)
    for(int j = 1; j < m; j++)
      prefix[i][j] += prefix[i][j - 1];
  for(int j = 1; j < m; j++)
    for(int i = 1; i < n; i++)
      prefix[i][j] += prefix[i - 1][j];
}

void build_partial(int n, int m, int q){
  partial.assign(n + 5, vector < ll > (m + 5));
  while(q--){
    Pair p1, p2;
    cin >> p1.fi >> p1.se >> p2.fi >> p2.se;
    if(p1.fi > p2.fi) swap(p1.fi, p2.fi);
    if(p1.se > p2.se) swap(p1.se, p2.se);
    partial[p2.fi][p2.se]++, partial[p2.fi][p1.se - 1]--, partial[p1.fi - 1][p2.se]--, partial[p1.fi - 1][p1.se - 1]++;
  }
  for(int i = n; i >= 0; i--)
    for(int j = m; j >= 0; j--)
      partial[i][j] += partial[i][j + 1];
  for(int i = n; i >= 0; i--)
    for(int j = m; j >= 0; j--)
      partial[i][j] += partial[i + 1][j];
}

int main(){
  AhMeD_HoSSaM();
  
  Time
  return 0;
}