#include <bits/stdc++.h>
#pragma GCC optimize("0")
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
#define INF 2'000'000'000
#define EPS 1e-9
#define PI acos(-1)
 
void AhMeD_HoSSaM(){
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
  #endif
}

int n, m;

vector < int > choice(int x, int y){
  if(x >= y * 2) return {x - 1};
  else if(x == 1) return {2};
  else return {x - 1, x * 2};
}

int BFS (int start, int finish){
  vector < int > path(1e5 + 1);
  vector < bool > vis(1e5 + 1);
  queue < int > bfs;
  bfs.push(start);
  if(start == finish) return 0;
  vis[start] = true;
  path[start] = 0;
  while(!bfs.empty()){
    int num = bfs.front(); 
    bfs.pop();
    for(auto& it : choice(num, m)){
        if(!vis[it]) vis[it] = true, bfs.push(it), path[it] = path[num] + 1;
        if(it == finish) return path[it];
    }
  }
  return -1;
}

int main(){
  AhMeD_HoSSaM();
   
  Time
  return 0;
}