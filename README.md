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

[🏆 Contest](#-contest) · [🕸️ Graph](#️-graph) · [🌲 Data Structures](#-data-structures) · [📊 Range Query](#-range-query) · [#️⃣ Hashing](#️-hashing) · [📈 Dynamic Programming](#-dynamic-programming) · [📝 String](#-string) · [π Number Theory](#-number-theory) · [📐 Math & Geometry](#-math--geometry) · [⚙️ Data Types](#️-data-types) · [🗜️ Compression](#️-compression) · [✂️ VS Code Snippets](#️-vs-code-snippets)

---

## 🏆 Contest

| Template | Description |
|----------|-------------|
| [Contest Template](cp_template.cpp) | Main C++ template with macros and common includes |

---

## 🕸️ Graph

| Template | Description |
|----------|-------------|
| [Graph Traversal](graph.cpp) | DFS & BFS on adjacency list graphs |
| [Graph Representation](graph_representation.cpp) | Adjacency list and adjacency matrix representations |
| [Dijkstra's Algorithm](dijkstra.cpp) | Single-source shortest path for non-negative weighted graphs |
| [Floyd-Warshall](floyd.cpp) | All-pairs shortest path in O(V³) |
| [Prim's MST](prim.cpp) | Minimum spanning tree using priority queue |
| [Bellman-Ford](bellman_ford.cpp) | SSSP supporting negative edge weights and cycle detection |
| [Centroid Decomposition](centroid_decomposition.cpp) | Divide-and-conquer on trees via centroid |
| [LCA — Binary Lifting](lca.cpp) | Lowest Common Ancestor with O(log n) queries |
| [LCA Weighted](lca_weighted.cpp) | LCA with path distance queries on weighted trees |
| [Tarjan's SCC](tarjan.cpp) | Strongly connected components, bridges, and articulation points |
| [Kuhn's Matching](kuhn.cpp) | Maximum bipartite matching via augmenting paths |
| [Link Cut Tree](link_cut_tree.cpp) | Dynamic tree connectivity with path queries in O(log n) |

---

## 🌲 Data Structures

| Template | Description |
|----------|-------------|
| [Binary Search Tree](binary_search_tree.cpp) | BST with insert, delete, search operations |
| [Segment Tree](seg_tree.cpp) | Point update, range query in O(log n) |
| [Segment Tree — Lazy](lazy_propagation.cpp) | Range update with lazy propagation in O(log n) |
| [Persistent Segment Tree](pst.cpp) | Immutable versioned segment tree for historical queries |
| [Segment Tree 2D](seg_tree_2d.cpp) | 2D segment tree for 2D range queries and updates |
| [Fenwick Tree (BIT)](fenwick_tree.cpp) | Binary indexed tree for prefix sum queries in O(log n) |
| [Fenwick Tree 2D](fenwick_tree_2d.cpp) | 2D BIT for 2D range sum queries |
| [Fenwick Tree Range](fenwick_tree_range.cpp) | BIT supporting both range updates and range queries |
| [Sparse Table](sparse_table.cpp) | Static RMQ in O(1) with O(n log n) preprocessing |
| [DSU / Union-Find](dsu.cpp) | Disjoint set union with path compression and union by rank |
| [Heavy Light Decomposition](hld.cpp) | Path and subtree queries on trees via HLD |
| [Ordered Set](ordered_set.cpp) | Policy-based order statistics tree: `find_by_order`, `order_of_key` |
| [Trie](trie.cpp) | Prefix tree for string insert and search |
| [Binary Trie](trie_binary.cpp) | Bit-based trie for XOR maximum and queries |
| [Monotonic Stack](monotonic_stacks.cpp) | Next greater/smaller element queries in O(n) |
| [Monotonic Queue](monotonic_queue.cpp) | Sliding window min/max in O(n) |
| [Implicit Splay Tree](implicit_splay_tree.cpp) | Implicit key splay tree for sequence split/merge operations |
| [Splay Tree](splay_tree.cpp) | Self-adjusting BST with amortized O(log n) operations |
| [Heap](heap.cpp) | Binary heap / priority queue implementation |

---

## 📊 Range Query

| Template | Description |
|----------|-------------|
| [SQRT Decomposition](sqrt_decomp.cpp) | Bucket decomposition for range queries in O(√n) |
| [Mo's Algorithm](mo.cpp) | Offline range queries sorted by Mo's ordering in O((n+q)√n) |
| [Mo's on Trees](mo_tree.cpp) | Mo's algorithm adapted for tree path queries |

---

## #️⃣ Hashing

| Template | Description |
|----------|-------------|
| [Rolling Hash](hash.cpp) | Polynomial rolling hash for O(1) substring comparisons |
| [Hashed Deque](hashed_deque.cpp) | Deque with rolling hash support for sliding window hashing |
| [Hash Segment Tree](hashing_segment_tree.cpp) | Segment tree storing hash values for range hash queries |

---

## 📈 Dynamic Programming

| Template | Description |
|----------|-------------|
| [Digit DP](dp_digits.cpp) | Count integers in [L,R] satisfying digit-based predicates |
| [Convex Hull Trick](convex_hull_trick.cpp) | Li Chao tree / CHT for linear DP transition optimization |
| [Kadane's Algorithm](kadane.cpp) | Maximum subarray sum in O(n) |
| [Manacher's Algorithm](manacher.cpp) | All palindromic substrings in O(n) |
| [Prefix Sum 2D](prefix_sum_2d.cpp) | 2D prefix sums for O(1) rectangle sum queries |
| [Partial Sum 2D](partial_sum_2d.cpp) | 2D difference array for O(1) rectangle updates |

---

## 📝 String

| Template | Description |
|----------|-------------|
| [KMP](kmp.cpp) | Knuth-Morris-Pratt pattern matching in O(n+m) |

---

## π Number Theory

| Template | Description |
|----------|-------------|
| [Sieve of Eratosthenes](sieve.cpp) | Find all primes up to N in O(N log log N) |
| [Sieve + Prime Factors](sieve_prime_factors.cpp) | Linear sieve precomputing smallest prime factor per number |
| [Factorization](factors.cpp) | Trial division and factorization algorithms |
| [Miller-Rabin](miller_rabin.cpp) | Deterministic primality test for large numbers |

---

## 📐 Math & Geometry

| Template | Description |
|----------|-------------|
| [Convex Hull](convex_hull.cpp) | Andrew's monotone chain convex hull in O(n log n) |
| [Math Utilities](math.cpp) | GCD, LCM, extended Euclidean and number utilities |
| [Matrix Exponentiation](matrix_power.cpp) | Fast matrix power for linear recurrences in O(k³ log n) |
| [Modular Inverse](power_inverse.cpp) | Modular inverse via Fermat's little theorem |
| [Geometry Points](point.cpp) | 2D point struct with cross/dot product and angle operations |
| [Ternary Search](ternary_search.cpp) | Find minimum/maximum of a unimodal function |

---

## ⚙️ Data Types

| Template | Description |
|----------|-------------|
| [Modular Integer](mod_int.cpp) | Integer wrapper type with automatic modular arithmetic |
| [Big Integer](big_int.cpp) | Arbitrary precision integer with arithmetic operations |

---

## 🗜️ Compression

| Template | Description |
|----------|-------------|
| [Coordinate Compression](coordinate_compression.cpp) | Map large sparse coordinate values to compact range |

---

## ✂️ VS Code Snippets

Drop any file from [`snippets/`](snippets/) into your project's `.vscode/` folder to activate it.

| Snippet File | Covers |
|---|---|
| [template.code-snippets](snippets/template.code-snippets) | CP contest template, Google template |
| [graphs.code-snippets](snippets/graphs.code-snippets) | Dijkstra, Floyd, LCA, HLD, Tarjan, LCT, Centroid, MoTree |
| [trees.code-snippets](snippets/trees.code-snippets) | Segment tree, Fenwick, Trie, Sparse table, PST, Splay |
| [data_structures.code-snippets](snippets/data_structures.code-snippets) | DSU, Heap, Monotonic stack/queue, Ordered set, Sqrt decomp |
| [math.code-snippets](snippets/math.code-snippets) | Miller-Rabin, ModInt, BigInt, Sieve, Matrix power |
| [dp.code-snippets](snippets/dp.code-snippets) | Digit DP, Kadane |
| [strings.code-snippets](snippets/strings.code-snippets) | KMP, Manacher, Rolling hash |
| [geometry.code-snippets](snippets/geometry.code-snippets) | Point struct, Convex hull, Convex hull trick |
| [algorithms.code-snippets](snippets/algorithms.code-snippets) | Mo's algorithm, Coord compression, Ternary search |

---

## 🔗 Additional Resources

| Resource | Description |
|----------|-------------|
| [Stress Testing](https://github.com/7oSkaaa/Stress_Testing) | Stress testing setup for solution validation |

---

<div align="center">

Made with ❤️ by <a href="https://7oskaaa.github.io/Ahmed-Hossam/">Ahmed Hossam</a>

</div>
