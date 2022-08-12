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

struct BST {

    int data;
    BST *left, *right;

    BST(int data = 0){
        this -> data = data;
        left = right = nullptr;
    }

    // Insert New node

    BST* Insert(BST* root, int val){
        if(!root) return new BST(val);
        if(val > root -> data)
            root -> right = Insert(root -> right, val);
        else
            root -> left = Insert(root -> left, val);
        return root;
    }

    // Inorder Traverse (LRR)

    void Inorder(BST* root){
        if(!root) return;
        Inorder(root -> left);
        cout << root -> data << " ";
        Inorder(root -> right);
    }

    // Preorde Traverse (RLR)

    void Preorder(BST* root){
        if(!root) return;
        cout << root -> data << " ";
        Preorder(root -> left);
        Preorder(root -> right);
    }

    // Postorder Traverse (LRR)

    void Postorder(BST* root){
        if(!root) return;
        Postorder(root -> left);
        Postorder(root -> right);
        cout << root -> data << " ";

    }

    // Traverse each level

    void Level_Order(BST* root){
        if(!root) return;
        queue < BST* > bfs;
        bfs.push(root);
        while(!bfs.empty()){
            BST* curr = bfs.front();
            bfs.pop();
            cout << curr -> data << " ";
            if(curr -> left)
                bfs.push(curr -> left);
            if(curr -> right)
                bfs.push(curr -> right);
        }
    }

    // Search on a node

    bool Search(BST* root, int val){
        if(!root) return false;
        if(root -> data == val) return true;
        if(val > root -> data) return Search(root -> right, val);
        else return Search(root -> left, val);
    }

    // Get minimum node in BST

    BST* minValueNode(BST* node){
        BST* current = node;
        while (current && current -> left != nullptr) current = current -> left;
        return current;
    }

    // Get maximum node in BST

    BST* maxValueNode(BST* node){
        BST* current = node;
        while (current && current -> right != nullptr) current = current -> right;
        return current;
    }

    // Delete Node

    BST* Delete_Node(BST* root, int key){
        if(!root) return root;
        if(key < root -> data)
            root -> left = Delete_Node(root -> left, key);
        else if(key > root -> data)
            root -> right = Delete_Node(root -> right, key);
        else {
            if(!root -> left && !root -> right) return nullptr;
            else if(!root -> left){
                BST* temp = root -> right;
                free(root);
                return temp;
            }else if(!root -> right){
                BST* temp = root -> left;
                free(root);
                return temp;
            }
            BST* temp = minValueNode(root -> right);
            root -> data = temp -> data;
            root -> right = Delete_Node(root -> right, temp -> data);
        }
        return root;
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