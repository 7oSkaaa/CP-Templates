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

struct Stack {
    
    vector < ll > s, GCD;
    
    Stack() {
        GCD = {0}, s = {};
    }

    void push(ll x){
        s.emplace_back(x);
        GCD.push_back(__gcd(GCD.back(), x));
    }

    ll pop(){
        ll res = s.back();
        s.pop_back();
        GCD.pop_back();
        return res;
    }
    
    bool empty(){
        return s.empty();
    }
    
    ll GCD_val(){
        return GCD.back();
    }

};

struct Queue_with_Stack {

    Stack s1, s2;

    Queue_with_Stack () {
        s1 = Stack(), s2 = Stack();
    }

    void push(ll x){
        s2.push(x);
    }

    void pop(){
        if(s1.empty())
            while(!s2.empty())
                s1.push(s2.pop());
        s1.pop();
    }

    bool is_good(){
        return __gcd(s1.GCD_val(), s2.GCD_val()) == 1;
    }

};

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