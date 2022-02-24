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
#define Num_of_Digits(n) ((int)log10(n) + 1)
#define mod_combine(a, b, m) (((a % m) * (b % m)) % m)
#define all(vec) vec.begin(), vec.end()
#define rall(vec) vec.rbegin(), vec.rend()
#define sz(x) int(x.size())
#define debug(x) cout << #x << ": " << (x) << "\n";
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

struct Kadane {
    
    // Minimum Contigours Subarray Sum

    ll Min_Subarray_Sum(vector < ll >& nums){
        ll Min_so_far = OO, Min_Curr = OO;
        for(auto& i : nums){
            Min_Curr += i;
            Min_so_far = min(Min_so_far, Min_Curr);
            Min_Curr = min(Min_Curr, 0ll);
        }
        return Min_so_far;
    }

    // Maximum Contigours Subarray Sum

    ll Max_Subarray_Sum(vector < ll >& nums){
        ll Max_so_far = -OO, Max_Curr = -OO;
        for(auto& i : nums){
            Max_Curr += i;
            Max_so_far = max(Max_so_far, Max_Curr);
            Max_Curr = min(Max_Curr, 0ll);
        }
        return Max_so_far;
    }

};

void Solve(){
    
}

int main(){
    AhMeD_HoSSaM();
    int t = 1;
    //cin >> t;
    while(t--)
        Solve();
    return 0;
} 