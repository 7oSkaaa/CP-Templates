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

struct KMP {

    string pattern;
    vector < int > lp;

    KMP(const string& str = "") : pattern(str) {
        build();
    }

    void build(){
        int n = sz(pattern);
        lp.resize(n);
        for(int i = 1; i < n; i++)
            lp[i] = failure(lp[i - 1], pattern[i]);
    }

    int failure(int idx, char nxt){
        while(idx > 0 && pattern[idx] != nxt)
            idx = lp[idx - 1];
        return idx + (pattern[idx] == nxt);
    }

    vector < int > match(const string& str){
        int n = sz(str), m = sz(pattern);
        vector < int > ret;
        for(int i = 0, k = 0; i < n; i++){
            k = failure(k, str[i]);
            if(k == m)
                ret.push_back(i - m + 1); // 0-based indexing
        }

        for(auto& idx : ret)
            idx++; // 1-based indexing
        
        return ret;
    }

    vector < int > count(const string& str){ // count number of occurrences of each prefix
        int n = sz(str), m = sz(pattern);
        vector < int > cnt(m + 1);
        for(int i = 1, k = 0; i < n; i++){
            k = failure(k, str[i]);
            cnt[k]++;
        }

        for(int i = m - 1; i > 0; i--)
            cnt[lp[i - 1]] += cnt[i]; // number of occurrences of prefix of length lp[i - 1] is at least cnt[i]
 
        for(int i = 0; i <= m; i++) 
            cnt[i]++; // add the whole substring itself
 
        return cnt;
    }

    vector < int > get_prefixes(){
        vector < int > indexes = {sz(pattern)};
        for(int i = lp[sz(pattern) - 1]; i > 0; i = lp[i - 1])
            indexes.push_back(i);
        sort(all(indexes)); // indexes of prefixes increasing
        return indexes;
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