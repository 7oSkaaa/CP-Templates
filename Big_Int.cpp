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

struct BigInt {

    const int BASE = 1000000000;
    vector < int > v;
    
    BigInt() {}

    BigInt(const long long &val) {
        *this = val;
    }
    
    BigInt(const string &val) {
        *this = val;
    
    }
    
    int size() const { return v.size(); }
    
    bool zero() const { return v.empty(); }
    
    BigInt& operator = (long long val) {
        v.clear();
        while (val) {
            v.push_back(val % BASE);
            val /= BASE;
        }
        return *this;
    }

    BigInt& operator = (const BigInt &a) {
        v = a.v;
        return *this;
    }

    BigInt& operator = (const vector < int > &a) {
        v = a;
        return *this;
    }

    BigInt& operator = (const string &s) {
        *this = 0;
        for (const char &ch : s)
            *this = *this * 10 + (ch - '0');
        return *this;
    }
    
    bool operator < (const BigInt &a) const {
        if (a.size() != size())
            return size() < a.size();
        for (int i = size() - 1; i >= 0; i--)
            if (v[i] != a.v[i])
                return v[i] < a.v[i];
        return false;
    }

    bool operator > (const BigInt &a) const {
        return a < *this;
    }

    bool operator == (const BigInt &a) const {
        return (!(*this < a) && !(a < *this));
    }

    bool operator <= (const BigInt &a) const {
        return ((*this < a) || !(a < *this));
    }
    
    ll val(){
        ll ans = 0;
        for (int i = 0; i < size(); i++)
            ans = ans * 10 + v[i];
        return ans;
    }

    BigInt operator + (const BigInt &a) const {
        BigInt res = *this;
        int idx = 0, carry = 0;
        while (idx < a.size() || carry) {
            if (idx < a.size())
                carry += a.v[idx];
            if (idx == res.size())
                res.v.push_back(0);
            res.v[idx] += carry;
            carry = res.v[idx] / BASE;
            res.v[idx] %= BASE;
            idx++;
        }
        return res;
    }
    
    BigInt& operator += (const BigInt &a) {
        *this = *this + a;
        return *this;
    }
    
    BigInt operator * (const BigInt &a) const {
        BigInt res;
        if (this -> zero() || a.zero())
            return res;
        res.v.resize(size() + a.size());
        for (int i = 0; i < size(); i++) {
            if (v[i] == 0)
                continue;
            long long carry = 0;
            for (int j = 0; carry || j < a.size(); j++) {
                carry += 1LL * v[i] * (j < a.size() ? a.v[j] : 0);
                while (i + j >= res.size())
                    res.v.push_back(0);
                carry += res.v[i + j];
                res.v[i + j] = carry % BASE;
                carry /= BASE;
            }
        }
        while (!res.v.empty() && res.v.back() == 0)
            res.v.pop_back();
        return res;
    }

    BigInt& operator *= (const BigInt &a) {
        *this = *this * a;
        return *this;
    }

    BigInt& operator -= (const BigInt &b){
        if(*this < b)
            throw("UNDERFLOW");
        int n = this -> size(), m = b.size();
        int i, t = 0, s;
        for (i = 0; i < n;i++){
            if(i < m)
                s = this -> v[i] - b.v[i]+ t;
            else
                s = this -> v[i] + t;
            if(s < 0)
                s += 10,
                t = -1;
            else
                t = 0;
            this -> v[i] = s;
        }
        while(n > 1 && this -> v[n - 1] == 0)
            this -> v.pop_back(),
            n--;
        return *this;
    }

    BigInt operator - (const BigInt&b){
        BigInt a = *this;
        a -= b;
        return a;
    }

    BigInt operator -- (const int){
        *this -= BigInt(1);
        return *this;
    }

    BigInt operator ++ (const int){
        *this += BigInt(1);
        return *this;
    }

    BigInt& operator /=(const ll a) {
        ll carry = 0;
        for (int i = (int) v.size() - 1; i >= 0; i--) {
            ll cur = v[i] + carry * BASE;
            v[i] = cur / a;
            carry = cur % a;
        }
        while (!v.empty() && v.back() == 0)
            v.pop_back();
        return *this;
    }
    
    BigInt operator / (const ll a) {
        ll carry = 0;
        vector < int > res = this -> v;
        for (int i = (int) res.size() - 1; i >= 0; i--) {
            ll cur = res[i] + carry * BASE;
            res[i] = cur / a;
            carry = cur % a;
        }
        BigInt ans;
        ans = res;
        return ans;
    }
    
    BigInt operator % (const ll a){
        ll res = 0;
        for (int i = (int) v.size() - 1; i >= 0; i--)
            res = (res * 10 + v[i]) % a;
        BigInt ans = res;
        return ans;
    }

    BigInt& operator %= (const ll a) {
        *this = *this % a;
        return *this;
    }

    friend ostream& operator<<(ostream &out, const BigInt &a) {
        out << (a.zero() ? 0 : a.v.back());
        for (int i = (int) a.v.size() - 2; i >= 0; i--)
            out << setfill('0') << setw(9) << a.v[i];
        return out;
    }

    friend istream& operator>>(istream &in, BigInt &a) {
        string s;
        in >> s;
        a = s;
        return in;
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
