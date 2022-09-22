#include <bits/stdc++.h>

using namespace std;

#define cin_2d(vec, n, m) for(int i = 0; i < n; i++) for(int j = 0; j < m && cin >> vec[i][j]; j++);
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define fixed(n) fixed << setprecision(n)
#define ceil(n, m) (((n) / (m)) + ((n) % (m) ? 1 : 0))
#define fill(vec, value) memset(vec, value, sizeof(vec));
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

struct Convex_Hull_Trick {

    struct Line {

        ll slope, yIntercept;

        Line(ll S, ll Y) : slope(S), yIntercept(Y) {}

        ll val(ll x){
            return slope * x + yIntercept;
        }

        ll inersect(Line other){
            return (other.yIntercept - yIntercept + (slope - other.slope - 1)) / (slope - other.slope);
        }

    };
    
    deque < pair < Line, ll > > lines;

    void insert(ll slope, ll yIntercept){
        
        Line newLine = Line(slope, yIntercept);
        
        while (sz(lines) > 1 && lines.back().second >= lines.back().first.inersect(newLine)) 
            lines.pop_back();
        
        if (lines.empty()) 
            lines.push_back({newLine, 0});
        else 
            lines.push_back({newLine, lines.back().first.inersect(newLine)});
    }

    ll query(ll x){
            
        while (sz(lines) > 1 && lines[1].second <= x) 
            lines.pop_front();
        
        return lines[0].first.val(x);
    }

    ll query_bs(ll x){
        auto query = *lower_bound(all(lines), make_pair(Line(0, 0), x), 
            [&](const pair < Line, ll >& a, const pair < Line, ll >& b){
                return a.second > b.second;
        });
        return query.first.val(x);
    }

};

void Solve(){
    
}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--)
        Solve();
    return 0;
}