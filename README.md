<div align="center">

<h1>⚡ CP Templates</h1>

<p><b>Ahmed Hossam's competitive programming reference library</b><br>
57 battle-tested algorithms & data structures, organized for contests</p>

[![Stars](https://img.shields.io/github/stars/7oSkaaa/CP-Templates?style=flat-square&color=00cfff&labelColor=0d1626&logo=github)](https://github.com/7oSkaaa/CP-Templates/stargazers)
[![Forks](https://img.shields.io/github/forks/7oSkaaa/CP-Templates?style=flat-square&color=7c5cfc&labelColor=0d1626&logo=github)](https://github.com/7oSkaaa/CP-Templates/network/members)
[![Language](https://img.shields.io/badge/C%2B%2B-17-00599C?style=flat-square&labelColor=0d1626&logo=cplusplus)](https://isocpp.org/)
[![Website](https://img.shields.io/badge/website-live-10b981?style=flat-square&labelColor=0d1626&logo=googlechrome&logoColor=white)](https://7oskaaa.github.io/CP-Templates/)

<br>

<a href="https://codeforces.com/profile/7oSkaaa" title="Codeforces">
  <img src="https://img.icons8.com/external-tal-revivo-shadow-tal-revivo/50/000000/external-codeforces-programming-competitions-and-contests-programming-community-logo-shadow-tal-revivo.png" width="36px"/>
</a>&ensp;
<a href="https://leetcode.com/7oSkaa/" title="LeetCode">
  <img src="https://img.icons8.com/external-tal-revivo-shadow-tal-revivo/50/000000/external-level-up-your-coding-skills-and-quickly-land-a-job-logo-shadow-tal-revivo.png" width="36px"/>
</a>&ensp;
<a href="https://atcoder.jp/users/ahmed_7oSkaa" title="AtCoder">
  <img src="https://iili.io/HTsq4wv.png" width="36px"/>
</a>&ensp;
<a href="https://www.codechef.com/users/ahmed_7oskaa" title="CodeChef">
  <img src="https://img.icons8.com/color/50/000000/codechef.png" width="36px"/>
</a>&ensp;
<a href="https://icpc.global/ICPCID/IW0X0CTD0ZV9" title="ICPC">
  <img src="https://iili.io/HTsBUfS.png" width="36px"/>
</a>

<br><br>

### [🌐 Browse the interactive website →](https://7oskaaa.github.io/CP-Templates/)
*Search, preview with syntax highlighting, and download any template in one click*

</div>

---

## 📋 Contents

[🏆 Contest](#-contest) · [🕸️ Graph](#️-graph) · [🌲 Data Structures](#-data-structures) · [📊 Range Query](#-range-query) · [#️⃣ Hashing](#️-hashing) · [📈 Dynamic Programming](#-dynamic-programming) · [📝 String](#-string) · [π Number Theory](#-number-theory) · [📐 Math & Geometry](#-math--geometry) · [⚙️ Data Types](#️-data-types) · [🗜️ Compression](#️-compression)

---

## 🏆 Contest

| Template | Description |
|----------|-------------|
| [Contest Template](Template.cpp) | Main C++ template with macros and common includes |

---

## 🕸️ Graph

| Template | Description |
|----------|-------------|
| [Graph Traversal](Graph.cpp) | DFS & BFS on adjacency list graphs |
| [Graph Representation](Graph_Representation.cpp) | Adjacency list and adjacency matrix representations |
| [Dijkstra's Algorithm](Dijkstra.cpp) | Single-source shortest path for non-negative weighted graphs |
| [Floyd-Warshall](Floyd.cpp) | All-pairs shortest path in O(V³) |
| [Prim's MST](Prim.cpp) | Minimum spanning tree using priority queue |
| [Bellman-Ford](Bellman_Ford.cpp) | SSSP supporting negative edge weights and cycle detection |
| [Centroid Decomposition](Centroid_Decomposition.cpp) | Divide-and-conquer on trees via centroid |
| [LCA — Binary Lifting](LCA.cpp) | Lowest Common Ancestor with O(log n) queries |
| [LCA Weighted](LCA_Weighted.cpp) | LCA with path distance queries on weighted trees |
| [Tarjan's SCC](Tarjan.cpp) | Strongly connected components, bridges, and articulation points |
| [Kuhn's Matching](Kuhn.cpp) | Maximum bipartite matching via augmenting paths |
| [Link Cut Tree](Link_Cut_Tree.cpp) | Dynamic tree connectivity with path queries in O(log n) |

---

## 🌲 Data Structures

| Template | Description |
|----------|-------------|
| [Binary Search Tree](Binary_Search_Tree.cpp) | BST with insert, delete, search operations |
| [Segment Tree](Seg_Tree.cpp) | Point update, range query in O(log n) |
| [Segment Tree — Lazy](Lazy_Propagation.cpp) | Range update with lazy propagation in O(log n) |
| [Persistent Segment Tree](PST.cpp) | Immutable versioned segment tree for historical queries |
| [Segment Tree 2D](Seg_Tree_2D.cpp) | 2D segment tree for 2D range queries and updates |
| [Fenwick Tree (BIT)](Fenwick_Tree.cpp) | Binary indexed tree for prefix sum queries in O(log n) |
| [Fenwick Tree 2D](Fenwick_Tree_2D.cpp) | 2D BIT for 2D range sum queries |
| [Fenwick Tree Range](Fenwick_Tree_Range.cpp) | BIT supporting both range updates and range queries |
| [Sparse Table](Sparse_Table.cpp) | Static RMQ in O(1) with O(n log n) preprocessing |
| [DSU / Union-Find](DSU.cpp) | Disjoint set union with path compression and union by rank |
| [Heavy Light Decomposition](HLD.cpp) | Path and subtree queries on trees via HLD |
| [Ordered Set](Ordered_Set.cpp) | Policy-based order statistics tree: `find_by_order`, `order_of_key` |
| [Trie](Trie.cpp) | Prefix tree for string insert and search |
| [Binary Trie](Trie_Binary.cpp) | Bit-based trie for XOR maximum and queries |
| [Monotonic Stack](Monotonic_Stacks.cpp) | Next greater/smaller element queries in O(n) |
| [Monotonic Queue](Monotonic_Queue.cpp) | Sliding window min/max in O(n) |
| [Implicit Splay Tree](Implicit_SplayTree.cpp) | Implicit key splay tree for sequence split/merge operations |
| [Splay Tree](SplayTree.cpp) | Self-adjusting BST with amortized O(log n) operations |
| [Heap](Heap.cpp) | Binary heap / priority queue implementation |

---

## 📊 Range Query

| Template | Description |
|----------|-------------|
| [SQRT Decomposition](SQRT_Decomp.cpp) | Bucket decomposition for range queries in O(√n) |
| [Mo's Algorithm](MO.cpp) | Offline range queries sorted by Mo's ordering in O((n+q)√n) |
| [Mo's on Trees](MO_Tree.cpp) | Mo's algorithm adapted for tree path queries |

---

## #️⃣ Hashing

| Template | Description |
|----------|-------------|
| [Rolling Hash](Hash.cpp) | Polynomial rolling hash for O(1) substring comparisons |
| [Hashed Deque](Hashed_Deque.cpp) | Deque with rolling hash support for sliding window hashing |
| [Hash Segment Tree](Hashing_SegmentTree.cpp) | Segment tree storing hash values for range hash queries |

---

## 📈 Dynamic Programming

| Template | Description |
|----------|-------------|
| [Convex Hull Trick](Convex_Hull_Trick.cpp) | Li Chao tree / CHT for linear DP transition optimization |
| [Kadane's Algorithm](Kadane.cpp) | Maximum subarray sum in O(n) |
| [Manacher's Algorithm](Manacher.cpp) | All palindromic substrings in O(n) |
| [Prefix Sum 2D](Prefix_Sum_2D.cpp) | 2D prefix sums for O(1) rectangle sum queries |
| [Partial Sum 2D](Partial_Sum_2D.cpp) | 2D difference array for O(1) rectangle updates |

---

## 📝 String

| Template | Description |
|----------|-------------|
| [KMP](KMP.cpp) | Knuth-Morris-Pratt pattern matching in O(n+m) |

---

## π Number Theory

| Template | Description |
|----------|-------------|
| [Sieve of Eratosthenes](Seive.cpp) | Find all primes up to N in O(N log log N) |
| [Sieve + Prime Factors](Seive_Prime_Factors.cpp) | Linear sieve precomputing smallest prime factor per number |
| [Factorization](Factors.cpp) | Trial division and factorization algorithms |
| [Miller-Rabin](Miller_Robin.cpp) | Deterministic primality test for large numbers |

---

## 📐 Math & Geometry

| Template | Description |
|----------|-------------|
| [Convex Hull](Convex_Hull.cpp) | Andrew's monotone chain convex hull in O(n log n) |
| [Math Utilities](Math.cpp) | GCD, LCM, extended Euclidean and number utilities |
| [Matrix Exponentiation](Matrix_Power.cpp) | Fast matrix power for linear recurrences in O(k³ log n) |
| [Modular Inverse](Power_Inverse.cpp) | Modular inverse via Fermat's little theorem |
| [Geometry Points](Point.cpp) | 2D point struct with cross/dot product and angle operations |
| [Ternary Search](Ternary_Search.cpp) | Find minimum/maximum of a unimodal function |

---

## ⚙️ Data Types

| Template | Description |
|----------|-------------|
| [Modular Integer](Mod_Int.cpp) | Integer wrapper type with automatic modular arithmetic |
| [Big Integer](Big_Int.cpp) | Arbitrary precision integer with arithmetic operations |

---

## 🗜️ Compression

| Template | Description |
|----------|-------------|
| [Coordinate Compression](Coordinate_Compression.cpp) | Map large sparse coordinate values to compact range |

---

## 🔗 Additional Resources

| Resource | Description |
|----------|-------------|
| [CP.code-snippets](CP.code-snippets) | VS Code snippets for all templates |
| [Print Template](Print_Template.cpp) | Template configured for formatted output |
| [Stress Testing](https://github.com/7oSkaaa/Stress_Testing) | Stress testing setup for solution validation |

---

<div align="center">

Made with ❤️ by <a href="https://7oskaaa.github.io/Ahmed-Hossam/">Ahmed Hossam</a>

</div>
