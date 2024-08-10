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

enum class TrieMode { Lowercase, Uppercase, Digits };
template < TrieMode Mode >
class Trie {
public:
    Trie() : root(new Node()) {}

    void insert(const string& word) {
        Node* curr = root;
        for (char c : word) {
            int index = charToIndex(c);
            if (!curr -> children[index]) 
                curr -> children[index] = new Node();
            curr = curr -> children[index];
            curr -> freq++;
        }
        curr -> is_word = true;
    }

    bool search(const string& word) const {
        const Node* curr = root;
        for (char c : word) {
            int index = charToIndex(c);
            if (!curr -> children[index]) return false;
            curr = curr -> children[index];
        }
        return curr -> is_word;
    }

    void erase(const string& word) {
        erase(word, 0, root);
    }

    bool is_prefix(const string& word) const {
        const Node* curr = root;
        for (char c : word) {
            int index = charToIndex(c);
            if (!curr -> children[index]) return false;
            curr = curr -> children[index];
        }
        return true;
    }
    
private:
    inline static constexpr int charSize() {
        switch (Mode) {
            case TrieMode::Lowercase: return 26;
            case TrieMode::Uppercase: return 26;
            case TrieMode::Digits:    return 10;
        }
        return 0; // Should never reach here
    }

    inline static int charToIndex(char c) {
        switch (Mode) {
            case TrieMode::Lowercase: return c - 'a';
            case TrieMode::Uppercase: return c - 'A';
            case TrieMode::Digits:    return c - '0';
        }
        return -1; // Should never reach here
    }

    struct Node {
        Node* children[charSize()] = {nullptr};
        bool is_word = false;
        int freq = 0;
    };

    Node* root;

    void erase(const std::string& word, size_t idx, Node* curr) {
        if (idx == word.size()) return curr -> is_word = false, void();
        int index = charToIndex(word[idx]);
        if (curr -> children[index]) {
            erase(word, idx + 1, curr -> children[index]);
            curr -> children[index] -> freq--;
            if (curr -> children[index] -> freq == 0) {
                delete curr -> children[index];
                curr -> children[index] = nullptr;
            }
        }
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