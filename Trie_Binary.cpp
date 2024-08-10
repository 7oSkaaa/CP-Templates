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

class Trie {
public:
    struct Node {
        Node* child[2];
        int freq;
        
        Node() : freq(0) {
            child[0] = child[1] = nullptr;
        }
    };

    Node* root;
    static constexpr int LOG = 30;

    Trie() : root(new Node()) {}

    void insert(int x) {
        Node* curr = root;
        for(int bit = LOG; bit >= 0; --bit) {
            int bit_val = get_bit(x, bit);
            if(!curr -> child[bit_val])
                curr -> child[bit_val] = new Node();
            curr = curr -> child[bit_val];
            ++curr -> freq;
        }
    }

    void erase(int x) {
        if (search(x)) {
            erase(x, LOG, root);
        }
    }

    bool search(int x) const {
        Node* curr = root;
        for(int bit = LOG; bit >= 0; --bit) {
            int bit_val = get_bit(x, bit);
            if(!curr -> child[bit_val]) {
                return false;
            }
            curr = curr -> child[bit_val];
        }
        return true;
    }
    
private:
    void erase(int x, int bit, Node* curr) {
        if(bit < 0) return;
        int bit_val = get_bit(x, bit);
        if (curr -> child[bit_val]) {
            erase(x, bit - 1, curr -> child[bit_val]);
            if (--curr -> child[bit_val] -> freq == 0) {
                delete curr -> child[bit_val];
                curr -> child[bit_val] = nullptr;
            }
        }
    }

    inline int get_bit(int x, int bit) const {
        return (x >> bit) & 1;
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