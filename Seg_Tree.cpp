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

ll combine(ll a, ll b){
    return a + b;
}

struct segtree {

    int size;
    vector < ll > tree; 
    
    void intial(int n){
        size = 1;
        while(size <= n) size *= 2;
        tree.assign(2 * size, 0ll);
    }

    segtree(int n){
        intial(n);
    }

    void build(vector < int >& nums, int idx, int lx, int rx){
        if(lx >= sz(nums)) return;
        if(rx == lx) tree[idx] = nums[lx];
        else {
            int m = (rx + lx) / 2;
            build(nums, 2 * idx, lx, m);
            build(nums, 2 * idx + 1, m + 1, rx);
            tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
        }
    }

    void build(vector < int >& nums){
        build(nums, 1, 1, size);
    }

    void update(int i, int v, int idx, int lx, int rx){
        if(rx == lx) tree[idx] = v;
        else {  
            int m = (rx + lx) / 2;
            if(i <= m) update(i, v, 2 * idx, lx, m);
            else update(i, v, 2 * idx + 1, m + 1, rx);
            tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
        }
    }

    void update(int i, int v){
        update(i, v, 1, 1, size);
    }

    ll query(int l, int r, int idx, int lx, int rx){
        if(lx > r || l > rx) return 0;
        if(lx >= l && rx <= r) return tree[idx];
        int m = (lx + rx) / 2;
        return combine(query(l, r, 2 * idx, lx, m), query(l, r, 2 * idx + 1, m + 1, rx));
    }

    ll query(int l, int r){
        return query(l, r, 1, 1, size);
    }
};

void solve(){
    int n, m;
    cin >> n >> m;
    vector < int > nums(n + 1);
    for(int i = 1; i <= n && cin >> nums[i]; i++);
    segtree st(n);
    st.build(nums);
    while(m--){
        int order;
        cin >> order;
        if(order == 1){
            int i, v;
            cin >> i >> v;
            st.update(i + 1, v);
        }else {
            int l, r;
            cin >> l >> r;
            cout << st.query(l + 1, r) << "\n";
        }
    }
}

int main(){
    AhMeD_HoSSaM();
    int t = 1;
    //cin >> t;
    while(t--)
        solve();
    Time
    return 0;
} 