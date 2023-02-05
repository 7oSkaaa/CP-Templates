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

struct Trie {
    
    struct Node {

        Node* child[26];
        bool is_word;
        int freq;

        Node(){
            memset(child, 0, sizeof(child));
            is_word = false;
            freq = 0;
        }
    };

    Node* root;
    char DEFAULT;

    Trie(){
        root = new Node;
        DEFAULT = 'a';
    }
    
    ~Trie(){
        Delete_Trie(root);
        delete root;
    }

    void Delete_Trie(Node* curr){
        for(auto& new_node : curr -> child){
            if(new_node){
                Delete_Trie(new_node);
                delete new_node;
            }
        }
    }

    void insert(string& word){
        Node* curr = root; 
        for(auto& c : word){
            if(!curr -> child[c - DEFAULT]) curr -> child[c - DEFAULT] = new Node;
            curr = curr -> child[c - DEFAULT];
            curr -> freq++;
        }
        curr -> is_word = true;
    }
  
    void erase(string& word, int idx, Node* curr){
        if(idx == sz(word)) return;
        erase(word, idx + 1, curr -> child[word[idx] - DEFAULT]);
        curr -> child[word[idx] - DEFAULT] -> freq--;
        if(curr -> child[word[idx] - DEFAULT] -> freq == 0){
            delete curr -> child[word[idx] - DEFAULT];
            curr -> child[word[idx] - DEFAULT] = nullptr;
        }
    }

    bool search(string& word){
        Node* curr = root; 
        for(auto& c : word){
            if(!curr -> child[c - DEFAULT]) return false;
            curr = curr -> child[c - DEFAULT];
        }
        return curr -> is_word;
    }
 
    void erase(string& word){
        if(search(word)) 
            erase(word, 0, root);
    }

    bool is_prefix(string& word){
        Node* curr = root; 
        for(auto& c : word){
            if(!curr -> child[c - DEFAULT]) return false;
            curr = curr -> child[c - DEFAULT];
        }
        return true;
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