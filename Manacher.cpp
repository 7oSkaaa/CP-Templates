#include <bits/stdc++.h>

using namespace std;

#define cin_2d(vec, n, m) for(int i = 0; i < n; i++) for(int j = 0; j < m && cin >> vec[i][j]; j++);
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define fixed(n) fixed << setprecision(n)
#define ceil(n, m) (((n) / (m)) + ((n) % (m) ? 1 : 0))
#define fill(vec, value) memset(vec, value, sizeof(vec));
#define mul_mod(a, b, m) (((a % m) * (b % m)) % m)
#define add_mod(a, b, m) (((a % m) + (b % m)) % m)
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

string longestPalSubstring(string& s){
    int strLen = 2 * sz(s) + 3, maxLen = 0, start = 0, maxRight = 0 ,center = 0;
    string str = "@#";
    for (char& c : s)
        str.push_back(c), str.push_back('#');
    str.push_back('$');
    vector < int > p(strLen);
    for(int i = 1; i < strLen - 1; i++){
        if (i < maxRight)
            p[i] = min(maxRight - i, p[2 * center - i]);
        while (str[i + p[i] + 1] == str[i - p[i] - 1]) p[i]++;
        if (i + p[i] > maxRight)
            center = i, maxRight = i + p[i];
        if (p[i] > maxLen)
            start = (i - p[i] - 1) / 2, maxLen = p[i];
    }
    return s.substr(start, maxLen);
}

void Solve(){
    
}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--)
        Solve();
    return 0;
}