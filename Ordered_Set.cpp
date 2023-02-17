#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template <typename K, typename V, typename Comp = std::less<K>>
using ordered_map = tree<K, V, Comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename Comp = std::less<K>>
using ordered_set = ordered_map<K, null_type, Comp>;

template <typename K, typename V, typename Comp = std::less_equal<K>>
using ordered_multimap = tree<K, V, Comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename Comp = std::less_equal<K>>
using ordered_multiset = ordered_multimap<K, null_type, Comp>;

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

template < typename T = int , typename CompFunction = std::less_equal < T > > struct Ordered_Multiset {
    
    ordered_multiset < T, CompFunction > mst;
    int Mode;

    // Constructor 
    Ordered_Multiset(bool isSmaller = true) {
        mst.clear();
        Mode = !isSmaller ? 1 : -1;
    }
    
    // Constructor with vector
    Ordered_Multiset(vector < T > &vec, bool isSmaller = true) {
        mst.clear();
        for (auto &x : vec) 
            mst.insert(x);
        Mode = !isSmaller ? 1 : -1;
    }

    // Insert element
    void insert(T val) {
        mst.insert(val);
    }

    // check if element exists or not
    bool is_exist(T val){ 
        if((mst.upper_bound(val)) == mst.end())
            return false;
        return ((*mst.upper_bound(val)) == val);
    }

    // erase element if exists
    void erase(T val){
        if(is_exist(val))
            mst.erase(mst.upper_bound(val));
    }
    
    // return element with given index
    T at(int idx){
        return (*mst.find_by_order(idx));
    }

    // return element with given index like mst[idx]
    T operator [] (int idx){
        return at(idx);
    }

    // return first index of element
    int first_idx(T val){ 
        if(!is_exist(val))
            return -1;
        return (mst.order_of_key(val));
    }

    // return last index of element
    int last_idx(T val){
        if(!is_exist(val))
            return -1;
        if(at(sz(mst) - 1) == val)
            return sz(mst) -1;
        return first_idx(*mst.lower_bound(val)) - 1;
    }

    // return number of occurences of element
    T count(T val){ 
        if(!is_exist(val))
            return 0;
        return last_idx(val) - first_idx(val) + 1;
    }

    // clear the ordered multiset
    void clear(){
        mst.clear();
    }

    // return size of ordered multiset
    int size(){
        return sz(mst);
    }

    // return number of elements < Comp > of val
    int order_of_key(T val){
        return mst.order_of_key(val - Mode);
    }

    // return iterator to element with given index
    typename ordered_multiset < T, CompFunction >::iterator find_by_order(int idx){
        return mst.find_by_order(idx);
    }

    // print the ordered multiset
    friend ostream& operator << (ostream &out, const Ordered_Multiset < T, CompFunction > &mst) { 
        for (const T &x : mst.mst) out << x << ' '; 
        return out;
    }

    // Ordered_Multiset < int, less_equal < int > > mst;
    // Ordered_Multiset < int, greater_equal < int > > mst;

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