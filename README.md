<div align="center">

# 🎯 a2Z DSA — Striver's A2Z DSA Sheet Solutions

[![Problems Solved](https://img.shields.io/badge/Solved-66%2F476-6366f1?style=for-the-badge&logo=leetcode&logoColor=white)](./dashboard/index.html)
[![Easy](https://img.shields.io/badge/Easy-24-22c55e?style=for-the-badge)](./dashboard/index.html)
[![Medium](https://img.shields.io/badge/Medium-29-f59e0b?style=for-the-badge)](./dashboard/index.html)
[![Hard](https://img.shields.io/badge/Hard-9-ef4444?style=for-the-badge)](./dashboard/index.html)
[![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](#)
[![Patterns](https://img.shields.io/badge/28_DSA_Patterns-8b5cf6?style=for-the-badge)](#-28-dsa-patterns)

**A structured DSA learning journey following [Striver's A2Z DSA Course](https://takeuforward.org/strivers-a2z-dsa-course/strivers-a2z-dsa-course-sheet-2/).**
Each solution includes C++ code, problem statements, and notes on approaches + complexity.

[📊 **Open Dashboard**](./dashboard/index.html) &nbsp;•&nbsp; [🧩 **28 Patterns**](#-28-dsa-patterns) &nbsp;•&nbsp; [🔍 **Search Tool**](#-tools) &nbsp;•&nbsp; [📋 **Full Sheet**](./Strivers_A2Z_Sheet_with_Patterns.md)

</div>

---

## 📊 Progress Overview

```
Overall:    ████░░░░░░░░░░░░░░░░░░░░░░░░░░  66/476 (13.9%)
Easy:       ███████░░░░░░░░░░░░░░░░░░░░░░░  24/158
Medium:     █████░░░░░░░░░░░░░░░░░░░░░░░░░  29/182
Hard:       ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░   9/136
Patterns:   12/28 active
```

> 💡 Run `python scripts/sync.py` to auto-update all stats and the dashboard.

---

## 🧩 28 DSA Patterns

The **28 most important DSA patterns** that cover every coding interview question. Each pattern below lists when to use it and key problems.

### 1. 👉 Two Pointers
> **When:** Sorted arrays, pair finding, palindromes, removing duplicates.
>
> | Problem | Difficulty |
> |---------|-----------|
> | [3Sum](https://leetcode.com/problems/3sum/) | Medium |
> | [4Sum](https://leetcode.com/problems/4sum/) | Medium |
> | [Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/) | Easy |
> | [Move Zeros to End](https://leetcode.com/problems/move-zeroes/) | Easy |
> | [Sort Colors (Dutch National Flag)](https://leetcode.com/problems/sort-colors/) | Medium |
> | [Next Permutation](https://leetcode.com/problems/next-permutation/) | Medium |
> | [Squares of a Sorted Array](https://leetcode.com/problems/squares-of-a-sorted-array/) | Easy |

### 2. 🪟 Sliding Window
> **When:** Subarray/substring problems, max/min in a window, k-length sequences.
>
> | Problem | Difficulty |
> |---------|-----------|
> | Longest Substring Without Repeating Characters | Medium |
> | Max Consecutive Ones III | Medium |
> | Minimum Window Substring | Hard |
> | Fruit Into Baskets | Medium |
> | Longest Repeating Character Replacement | Hard |

### 3. 🔍 Binary Search
> **When:** Sorted data, search space reduction, answer-on-answer problems.
>
> | Problem | Difficulty |
> |---------|-----------|
> | [Binary Search](https://leetcode.com/problems/binary-search/) | Easy |
> | [Search Insert Position](https://leetcode.com/problems/search-insert-position/) | Easy |
> | [Search in Rotated Sorted Array II](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/) | Medium |
> | [Find Peak Element](https://leetcode.com/problems/find-peak-element/) | Medium |
> | [Capacity to Ship Packages](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/) | Medium |
> | [Kth Missing Positive Number](https://leetcode.com/problems/kth-missing-positive-number/) | Easy |
> | [Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/) | Hard |
> | [Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/) | Hard |

### 4. ➕ Prefix Sum
> **When:** Subarray sum queries, range sum operations.
>
> | Problem | Difficulty |
> |---------|-----------|
> | [Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/) | Medium |
> | Largest Subarray with Sum 0 | Medium |
> | Count Subarrays with Given XOR K | Hard |

### 5. 🗂️ Hash Maps
> **When:** Counting, grouping, finding duplicates, two-sum style lookups.
>
> | Problem | Difficulty |
> |---------|-----------|
> | [Two Sum](https://leetcode.com/problems/two-sum/) | Easy |
> | [Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/) | Medium |
> | [Valid Anagram](https://leetcode.com/problems/valid-anagram/) | Easy |
> | [Isomorphic Strings](https://leetcode.com/problems/isomorphic-strings/) | Easy |
> | [Sort Characters by Frequency](https://leetcode.com/problems/sort-characters-by-frequency/) | Medium |
> | [Set Matrix Zeroes](https://leetcode.com/problems/set-matrix-zeroes/) | Medium |

### 6. 📚 Monotonic Stack
> **When:** Next greater/smaller element, histogram problems, trapping rain water.
>
> | Problem | Difficulty |
> |---------|-----------|
> | Next Greater Element | Medium |
> | Trapping Rain Water | Hard |
> | Largest Rectangle in Histogram | Hard |
> | Sum of Subarray Minimums | Medium |

### 7. 🐢 Fast & Slow Pointers
> **When:** Cycle detection, finding middle node, linked list intersection.
>
> | Problem | Difficulty |
> |---------|-----------|
> | Middle of Linked List | Easy |
> | Detect a Loop in LL | Medium |
> | Find Starting Point in LL | Medium |
> | Check if LL is Palindrome | Medium |

### 8. 🔄 In-place Reversal of LinkedList
> **When:** Reverse full/partial linked list, k-group reversal.
>
> | Problem | Difficulty |
> |---------|-----------|
> | Reverse a Linked List | Medium |
> | Reverse LL in Group of Size K | Hard |
> | Rotate a Linked List | Hard |

### 9. 📐 Merge Intervals
> **When:** Overlapping ranges, scheduling, interval operations.
>
> | Problem | Difficulty |
> |---------|-----------|
> | [Merge Intervals](https://leetcode.com/problems/merge-intervals/) | Medium |
> | Insert Interval | Medium |
> | Non-overlapping Intervals | Medium |

### 10. 📈 Kadane's Algorithm
> **When:** Maximum subarray sum, contiguous sum optimization.
>
> | Problem | Difficulty |
> |---------|-----------|
> | [Maximum Subarray](https://leetcode.com/problems/maximum-subarray/) | Medium |
> | [Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/) | Medium |
> | [Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) | Easy |

### 11. 🗳️ Boyer-Moore Voting
> **When:** Finding elements appearing > n/2 or > n/3 times.
>
> | Problem | Difficulty |
> |---------|-----------|
> | [Majority Element](https://leetcode.com/problems/majority-element/) | Easy |
> | [Majority Element II](https://leetcode.com/problems/majority-element-ii/) | Medium |

### 12. 🇳🇱 Dutch National Flag
> **When:** Sort 3 categories (0/1/2), three-way partitioning.
>
> | Problem | Difficulty |
> |---------|-----------|
> | [Sort Colors](https://leetcode.com/problems/sort-colors/) | Medium |

### 13. ✂️ Divide & Conquer
> **When:** Merge sort, quick sort, inversions counting.
>
> | Problem | Difficulty |
> |---------|-----------|
> | [Sort an Array (Merge Sort)](https://leetcode.com/problems/sort-an-array/) | Medium |
> | [Reverse Pairs](https://leetcode.com/problems/reverse-pairs/) | Hard |
> | [Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/) | Hard |

### 14. 🔁 Recursion & Backtracking
> **When:** Permutations, combinations, constraint satisfaction (N-Queens, Sudoku).
>
> | Problem | Difficulty |
> |---------|-----------|
> | Combination Sum | Medium |
> | Subsets I & II | Medium |
> | N-Queens | Hard |
> | Sudoku Solver | Hard |
> | Palindrome Partitioning | Hard |
> | Generate Parentheses | Medium |

### 15. 🔢 Bit Manipulation
> **When:** XOR tricks, power of 2, single number, subsets via bitmask.
>
> | Problem | Difficulty |
> |---------|-----------|
> | [Single Number](https://leetcode.com/problems/single-number/) | Easy |
> | [Power of Two](https://leetcode.com/problems/power-of-two/) | Easy |
> | [XOR Operation in Array](https://leetcode.com/problems/xor-operation-in-an-array/) | Easy |

### 16. 🤑 Greedy
> **When:** Scheduling, interval selection, optimal ordering.
>
> | Problem | Difficulty |
> |---------|-----------|
> | Assign Cookies | Easy |
> | Jump Game I & II | Easy/Medium |
> | Fractional Knapsack | Medium |
> | Job Sequencing | Medium |
> | Candy | Hard |

### 17–20. 🏔️ Heap Patterns
> **17. Kth / K-closest** — Top K elements, kth largest.
> **18. Heap as Pointer** — Merge k sorted lists/arrays.
> **19. Greedy + Heap** — Task scheduling, optimization.
> **20. Two Heaps** — Find median in stream, sliding window median.
>
> | Problem | Difficulty | Sub-Pattern |
> |---------|-----------|-------------|
> | Kth Largest Element | Medium | Kth |
> | Merge K Sorted Lists | Hard | Pointer |
> | Task Scheduler | Medium | Greedy+Heap |
> | Find Median from Data Stream | Hard | Two Heaps |
> | Top K Frequent Elements | Medium | Kth |

### 21–25. 🌳 Tree Patterns
> **21. Traversal** — Pre/In/Post/Level order.
> **22. Mirror & Symmetry** — Invert tree, symmetric checks.
> **23. Search / LCA** — BST operations, lowest common ancestor.
> **24. Path Sum** — Root-to-leaf paths, max path sum.
> **25. Construction** — Build from preorder+inorder, sorted array to BST.
>
> | Problem | Difficulty | Sub-Pattern |
> |---------|-----------|-------------|
> | Inorder/Preorder/Postorder Traversal | Easy | Traversal |
> | Level Order / Zigzag Traversal | Medium | Traversal |
> | Symmetric Binary Tree | Medium | Mirror |
> | LCA of Binary Tree | Hard | Search |
> | Maximum Path Sum | Medium | Path Sum |
> | Construct BT from Preorder+Inorder | Hard | Construction |

### 26. 🕸️ Graphs: BFS / DFS
> **When:** Connected components, islands, cycle detection, flood fill, topo sort.
>
> | Problem | Difficulty |
> |---------|-----------|
> | Number of Islands | Medium |
> | Rotten Oranges | Medium |
> | Cycle Detection (Undirected/Directed) | Hard |
> | Topological Sort | Hard |
> | Bipartite Graph | Hard |
> | Word Ladder | Hard |

### 27. 🗺️ Graphs: Shortest Path
> **When:** Weighted graphs, minimum cost paths, network delays.
>
> | Problem | Difficulty |
> |---------|-----------|
> | Dijkstra's Algorithm | Hard |
> | Bellman-Ford Algorithm | Hard |
> | Floyd Warshall | Hard |
> | Network Delay Time | Medium |
> | Cheapest Flights Within K Stops | Hard |

### 28. 🧮 DP (Dynamic Programming)
> **When:** Optimization, counting, string matching, knapsack, LIS, LCS.
>
> | Problem | Difficulty |
> |---------|-----------|
> | [Fibonacci Number](https://leetcode.com/problems/fibonacci-number/) | Easy |
> | Climbing Stairs | Medium |
> | House Robber | Medium |
> | 0/1 Knapsack | Medium |
> | Longest Common Subsequence | Hard |
> | Longest Increasing Subsequence | Medium |
> | Edit Distance | Hard |
> | Matrix Chain Multiplication | Hard |

---

## 📚 Topic-wise Progress

| Topic | Solved | Total | Progress |
|-------|--------|-------|----------|
| Learn the Basics | ✅ | 56 | 🟩🟩⬜⬜⬜ |
| Sorting | ✅ | 7 | 🟩🟩🟩⬜⬜ |
| Arrays (Easy + Medium + Hard) | ✅ | 42 | 🟩🟩🟩⬜⬜ |
| Binary Search (1D + Answers + 2D) | ✅ | 32 | 🟩🟩⬜⬜⬜ |
| Strings (Basic + Medium + Hard) | ✅ | 23 | 🟩⬜⬜⬜⬜ |
| Linked Lists | ⬜ | 30 | ⬜⬜⬜⬜⬜ |
| Recursion & Backtracking | ⬜ | 24 | ⬜⬜⬜⬜⬜ |
| Bit Manipulation | ⬜ | 18 | ⬜⬜⬜⬜⬜ |
| Stack & Queue | ⬜ | 30 | ⬜⬜⬜⬜⬜ |
| Sliding Window | ⬜ | 12 | ⬜⬜⬜⬜⬜ |
| Heaps | ⬜ | 15 | ⬜⬜⬜⬜⬜ |
| Greedy | ⬜ | 16 | ⬜⬜⬜⬜⬜ |
| Binary Trees | ⬜ | 38 | ⬜⬜⬜⬜⬜ |
| BST | ⬜ | 16 | ⬜⬜⬜⬜⬜ |
| Graphs | ⬜ | 53 | ⬜⬜⬜⬜⬜ |
| Dynamic Programming | ⬜ | 55 | ⬜⬜⬜⬜⬜ |
| Tries | ⬜ | 7 | ⬜⬜⬜⬜⬜ |

> 📊 For detailed, live progress with interactive charts → [**Open Dashboard**](./dashboard/index.html)

---

## 🛠️ Tools

### 📊 Progress Dashboard
```bash
# Open dashboard/index.html in your browser — works 100% offline
start dashboard/index.html    # Windows
open dashboard/index.html     # macOS
```

### 🔄 Auto-Sync Script
```bash
python scripts/sync.py
# Scans solution folders, updates stats, generates dashboard data
```

### 🔍 Search & Filter CLI
```bash
python scripts/search.py --pattern "Two Pointers"       # Filter by pattern
python scripts/search.py --difficulty hard --solved       # Hard + solved only
python scripts/search.py --topic "Binary Search"          # Filter by topic
python scripts/search.py --unsolved --difficulty easy     # Easy unsolved
python scripts/search.py --query "palindrome"             # Keyword search
python scripts/search.py --list-patterns                  # List all patterns
python scripts/search.py --stats                          # Overall statistics
```

### 📝 Generate Notes
```bash
python scripts/generate_notes.py           # Generate NOTES.md for all solutions
python scripts/generate_notes.py --force   # Overwrite existing notes
```

---

## 📂 Repository Structure

```
a2Z_DSA/
├── dashboard/                         ← 📊 Visual progress dashboard
│   ├── index.html                     ← Open this in browser
│   ├── style.css
│   ├── app.js
│   └── data.js                        ← Auto-generated by sync
├── scripts/                           ← 🛠️ Automation tools
│   ├── sync.py                        ← Auto-sync everything
│   ├── search.py                      ← CLI search/filter
│   └── generate_notes.py             ← Generate NOTES.md stubs
├── templates/
│   └── NOTES_TEMPLATE.md             ← Note-taking template
├── 0001-two-sum/                      ← LeetCode solutions (65+)
│   ├── 0001-two-sum.cpp
│   ├── README.md
│   └── NOTES.md
├── 1_Basics/                          ← Topic-wise practice
├── 2_Sorting/
├── 3_Arrays/
├── Linkedlist/
├── Strivers_A2Z_Sheet_with_Patterns.csv
├── DSA patterns Cheat Sheet.xlsx      ← 28 patterns reference
└── stats.json
```

---

## 📖 References

- [Striver's A2Z DSA Course Sheet](https://takeuforward.org/strivers-a2z-dsa-course/strivers-a2z-dsa-course-sheet-2/)
- [Striver's YouTube Channel](https://www.youtube.com/@takeUforward)
- [A2Z Full Notes PDF](./Striver%20A2Z%20Full%20Notes%20-%20all%20approaches%20included%2C%20Prepared%20by%20Vinay%20kajla%20IG-%20Vinay.Kajla_.pdf)

---

<div align="center">

**Built with ❤️ by [gitkrypton18](https://github.com/gitkrypton18)**

*Keep grinding. Every problem makes you stronger.* 💪

</div>