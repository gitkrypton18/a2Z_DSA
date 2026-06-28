#!/usr/bin/env python3
"""
sync.py — Auto-sync script for a2Z_DSA repository.

Scans solution folders, cross-references with Striver's A2Z CSV sheet,
and generates dashboard/data.js with fresh statistics.

Usage:
    python scripts/sync.py
"""

import os
import csv
import json
import re
import subprocess
from datetime import datetime
from pathlib import Path
from collections import defaultdict, OrderedDict

# ─── Paths ─────────────────────────────────────────────────
REPO_ROOT = Path(__file__).resolve().parent.parent
CSV_PATH = REPO_ROOT / "Strivers_A2Z_Sheet_with_Patterns.csv"
STATS_PATH = REPO_ROOT / "stats.json"
DATA_JS_PATH = REPO_ROOT / "dashboard" / "data.js"

# ─── The 28 DSA Patterns ──────────────────────────────────
PATTERNS_CONFIG = [
    {"id": 1,  "name": "Two Pointers",                  "emoji": "👉",  "color": "#6366f1",
     "description": "Two pointers traversing from different positions",
     "whenToUse": "Sorted arrays, pair finding, palindromes, removing duplicates",
     "keywords": ["two pointers", "two pointer"]},

    {"id": 2,  "name": "Sliding Window",                 "emoji": "🪟",  "color": "#8b5cf6",
     "description": "Maintain a window that slides over data to track a subset",
     "whenToUse": "Subarray/substring problems, max/min in window, k-length",
     "keywords": ["sliding window"]},

    {"id": 3,  "name": "Binary Search",                  "emoji": "🔍",  "color": "#06b6d4",
     "description": "Divide search space in half each step",
     "whenToUse": "Sorted data, search space reduction, answer-on-answer",
     "keywords": ["binary search"]},

    {"id": 4,  "name": "Prefix Sum",                     "emoji": "➕",  "color": "#14b8a6",
     "description": "Pre-compute cumulative sums for O(1) range queries",
     "whenToUse": "Subarray sum queries, range operations",
     "keywords": ["prefix sum"]},

    {"id": 5,  "name": "Hash Maps",                      "emoji": "🗂️",  "color": "#f59e0b",
     "description": "O(1) lookups and frequency counting via hash tables",
     "whenToUse": "Counting, grouping, duplicates, two-sum style",
     "keywords": ["hash map", "hash maps", "hashing", "rolling hash"]},

    {"id": 6,  "name": "Monotonic Stack",                "emoji": "📚",  "color": "#ef4444",
     "description": "Stack maintaining increasing/decreasing order",
     "whenToUse": "Next greater/smaller element, histogram, trapping rain water",
     "keywords": ["monotonic stack", "monotonic queue"]},

    {"id": 7,  "name": "Fast & Slow Pointers",           "emoji": "🐢",  "color": "#22c55e",
     "description": "Two pointers moving at different speeds (Floyd's cycle detection)",
     "whenToUse": "Cycle detection, finding middle node, linked list problems",
     "keywords": ["fast & slow", "fast and slow", "tortoisehare"]},

    {"id": 8,  "name": "In-place Reversal of LinkedList", "emoji": "🔄",  "color": "#a855f7",
     "description": "Reverse linked list nodes in-place without extra space",
     "whenToUse": "Reverse full/partial linked list, k-group reversal",
     "keywords": ["in-place reversal of a linkedlist", "in-place reversal"]},

    {"id": 9,  "name": "Merge Intervals",                "emoji": "📐",  "color": "#ec4899",
     "description": "Merge or process overlapping intervals",
     "whenToUse": "Overlapping ranges, scheduling, interval operations",
     "keywords": ["merge intervals"]},

    {"id": 10, "name": "Kadane's Algorithm",              "emoji": "📈",  "color": "#f97316",
     "description": "Track max/min subarray sum in a single pass",
     "whenToUse": "Maximum subarray, contiguous sum optimization",
     "keywords": ["kadane"]},

    {"id": 11, "name": "Boyer-Moore Voting",              "emoji": "🗳️",  "color": "#84cc16",
     "description": "Find majority element in linear time, constant space",
     "whenToUse": "Elements appearing > n/2 or n/3 times",
     "keywords": ["boyer-moore", "boyer moore"]},

    {"id": 12, "name": "Dutch National Flag",             "emoji": "🇳🇱",  "color": "#0ea5e9",
     "description": "Three-way partitioning in a single pass",
     "whenToUse": "Sort 3 categories (0/1/2), three-way partition",
     "keywords": ["dutch national flag"]},

    {"id": 13, "name": "Divide & Conquer",                "emoji": "✂️",   "color": "#d946ef",
     "description": "Break problem into subproblems, solve, and combine",
     "whenToUse": "Merge sort, quick sort, inversions counting",
     "keywords": ["divide & conquer", "divide and conquer"]},

    {"id": 14, "name": "Recursion & Backtracking",        "emoji": "🔁",  "color": "#f43f5e",
     "description": "Explore all possibilities, backtrack on invalid paths",
     "whenToUse": "Permutations, combinations, constraint satisfaction (N-Queens, Sudoku)",
     "keywords": ["recursion and backtracking", "backtracking"]},

    {"id": 15, "name": "Bit Manipulation",                "emoji": "🔢",  "color": "#64748b",
     "description": "Use bitwise operations for efficient computation",
     "whenToUse": "XOR tricks, power of 2, single number, subsets via bitmask",
     "keywords": ["bit manipulation"]},

    {"id": 16, "name": "Greedy",                          "emoji": "🤑",  "color": "#16a34a",
     "description": "Make locally optimal choice at each step",
     "whenToUse": "Scheduling, interval selection, optimal ordering",
     "keywords": ["greedy"]},

    {"id": 17, "name": "Heap: Kth / K-closest",           "emoji": "🏔️",  "color": "#e11d48",
     "description": "Use heap to efficiently find kth largest/smallest",
     "whenToUse": "Top K elements, kth largest, k closest points",
     "keywords": ["kth", "k closest"]},

    {"id": 18, "name": "Heap: Heap as Pointer",           "emoji": "👆",  "color": "#be185d",
     "description": "Use heap to merge multiple sorted sequences",
     "whenToUse": "Merge k sorted lists/arrays, external sort",
     "keywords": ["heap as pointer"]},

    {"id": 19, "name": "Heap: Greedy + Heap",             "emoji": "💰",  "color": "#9333ea",
     "description": "Combine greedy strategy with heap for optimization",
     "whenToUse": "Task scheduling, resource allocation, IPO",
     "keywords": ["greedy+heap"]},

    {"id": 20, "name": "Heap: Two Heaps",                 "emoji": "⚖️",   "color": "#7c3aed",
     "description": "Use min-heap and max-heap together",
     "whenToUse": "Find median in stream, sliding window median",
     "keywords": ["2 heaps", "two heaps"]},

    {"id": 21, "name": "Tree: Traversal",                 "emoji": "🌳",  "color": "#059669",
     "description": "Visit tree nodes in pre/in/post/level order",
     "whenToUse": "Tree processing, serialization, level-based ops",
     "keywords": ["tree pattern: traversal"]},

    {"id": 22, "name": "Tree: Mirror & Symmetry",         "emoji": "🪞",  "color": "#0d9488",
     "description": "Check or create mirror/symmetric tree structures",
     "whenToUse": "Symmetric tree, invert tree, same tree checks",
     "keywords": ["mirror and symmetry"]},

    {"id": 23, "name": "Tree: Search / LCA",              "emoji": "🔎",  "color": "#0891b2",
     "description": "Search in BST, find lowest common ancestor",
     "whenToUse": "BST operations, LCA queries, kth smallest in BST",
     "keywords": ["tree pattern: search"]},

    {"id": 24, "name": "Tree: Path Sum",                  "emoji": "🛤️",  "color": "#0284c7",
     "description": "Track path values from root to leaf or any node",
     "whenToUse": "Path sum, root-to-leaf paths, max path sum",
     "keywords": ["path sum"]},

    {"id": 25, "name": "Tree: Construction",              "emoji": "🏗️",  "color": "#2563eb",
     "description": "Build trees from traversal sequences or sorted data",
     "whenToUse": "Construct from preorder+inorder, sorted array to BST",
     "keywords": ["tree pattern: construction", "construction"]},

    {"id": 26, "name": "Graphs: BFS / DFS",               "emoji": "🕸️",  "color": "#4f46e5",
     "description": "Traverse graphs using breadth-first or depth-first search",
     "whenToUse": "Connected components, islands, cycle detection, flood fill",
     "keywords": ["graphs:", "bfs/dfs", "topo sort", "tarjan", "strongly connected",
                  "mst", "dsu", "union-find"]},

    {"id": 27, "name": "Graphs: Shortest Path",           "emoji": "🗺️",  "color": "#7c3aed",
     "description": "Dijkstra, Bellman-Ford, Floyd-Warshall algorithms",
     "whenToUse": "Weighted graphs, minimum cost paths, network delays",
     "keywords": ["shortest path", "dijkstra", "bellman ford", "floyd warshall"]},

    {"id": 28, "name": "DP (Dynamic Programming)",        "emoji": "🧮",  "color": "#c026d3",
     "description": "Solve overlapping subproblems with memoization/tabulation",
     "whenToUse": "Optimization, counting, string matching, knapsack, LIS, LCS",
     "keywords": ["dp (dynamic programming)", "dp:"]},
]

# ─── Known Folder → CSV Name Mappings ─────────────────────
# LeetCode folder names that don't directly match Striver's A2Z CSV names
FOLDER_TO_CSV = {
    "maximum-subarray":                         "Kadane's Algorithm",
    "sort-colors":                              "Sort array of 0's 1's and 2's",
    "best-time-to-buy-and-sell-stock":          "Stock Buy and Sell",
    "spiral-matrix":                            "Print matrix in spiral manner",
    "rotate-image":                             "Rotate matrix by 90 degrees",
    "single-number":                            "Find number that appears once (others twice)",
    "max-consecutive-ones":                     "Maximum Consecutive Ones",
    "majority-element":                         "Majority Element-I",
    "majority-element-ii":                      "Majority Element-II",
    "subarray-sum-equals-k":                    "Count subarrays with given sum",
    "merge-sorted-array":                       "Merge two sorted arrays without extra space",
    "binary-search":                            "Search X in sorted array",
    "reverse-integer":                          "Reverse a number",
    "palindrome-number":                        "Check Palindrome",
    "sqrtx":                                    "Find square root of a number",
    "power-of-two":                             "Check if Number is Power of 2",
    "valid-anagram":                            "Check if two strings are anagram",
    "valid-palindrome":                         "Check Palindrome",
    "rotate-array":                             "Left Rotate Array by K Places",
    "sort-an-array":                            "Merge Sort",
    "merge-intervals":                          "Merge Overlapping Subintervals",
    "pascals-triangle":                         "Pascal's Triangle I",
    "find-missing-and-repeated-values":         "Find repeating and missing number",
    "fibonacci-number":                         "N-th Fibonacci number",
    "magnetic-force-between-two-balls":         "Aggressive Cows",
    "median-of-two-sorted-arrays":              "Median of 2 sorted arrays",
    "3sum":                                     "3 Sum",
    "4sum":                                     "4 Sum",
    "isomorphic-strings":                       "Isomorphic String",
    "check-if-array-is-sorted-and-rotated":     "Check if Array is Sorted",
    "minimum-number-of-days-to-make-m-bouquets":"Minimum days to make M bouquets",
    "add-digits":                               "Sum of all divisors",
    "xor-operation-in-an-array":                "XOR of numbers in given range",
    "integer-to-roman":                         "Roman to Integer",
    "find-first-and-last-position-of-element-in-sorted-array": "First and last occurrence",
    "search-in-rotated-sorted-array-ii":        "Search in rotated sorted array-II",
    "find-minimum-in-rotated-sorted-array":     "Find minimum in Rotated Sorted Array",
    "single-element-in-a-sorted-array":         "Single element in Sorted Array",
    "find-peak-element":                        "Find peak element",
    "maximum-product-subarray":                 "Maximum Product Subarray",
    "search-insert-position":                   "Search insert position",
    "search-a-2d-matrix":                       "Search in a 2D matrix",
    "search-a-2d-matrix-ii":                    "Search in 2D matrix - II",
    "find-a-peak-element-ii":                   "Find Peak Element - II",
    "remove-outermost-parentheses":             "Remove Outermost Parentheses",
    "largest-odd-number-in-string":             "Largest Odd Number in a String",
    "longest-common-prefix":                    "Longest Common Prefix",
    "sort-characters-by-frequency":             "Sort Characters by Frequency",
    "maximum-nesting-depth-of-the-parentheses": "Maximum Nesting Depth of Parentheses",
    "sum-of-beauty-of-all-substrings":          "Sum of Beauty of All Substrings",
    "rearrange-array-elements-by-sign":         "Rearrange array elements by sign",
    "reverse-pairs":                            "Reverse Pairs",
    "set-matrix-zeroes":                        "Set Matrix Zeroes",
    "longest-consecutive-sequence":             "Longest Consecutive Sequence",
    "remove-duplicates-from-sorted-array":      "Remove duplicates from Sorted array",
    "move-zeroes":                              "Move Zeros to End",
    "next-permutation":                         "Next Permutation",
    "rotate-string":                            "Rotate String",
    "capacity-to-ship-packages-within-d-days":  "Capacity to Ship Packages Within D Days",
    "kth-missing-positive-number":              "Kth Missing Positive Number",
    "find-the-smallest-divisor-given-a-threshold":"Find the smallest divisor",
    "split-array-largest-sum":                  "Split array - largest sum",
}

# ─── Topic Grouping ───────────────────────────────────────
TOPIC_GROUPS = OrderedDict([
    ("Learn the Basics",   ["Learn the Basics"]),
    ("Sorting",            ["Sorting-I", "Sorting-II"]),
    ("Arrays",             ["Arrays - Easy", "Arrays - Medium", "Arrays - Hard"]),
    ("Binary Search",      ["Binary Search - 1D", "Binary Search - Answers", "Binary Search - 2D"]),
    ("Strings",            ["Strings - Basic", "Strings - Medium", "Strings - Hard"]),
    ("Linked Lists",       ["Linked List - Singly", "Linked List - Doubly",
                            "Linked List - Medium", "Linked List - DLL Medium", "Linked List - Hard"]),
    ("Recursion",          ["Recursion - Basic", "Recursion - Subsequences", "Recursion - Hard"]),
    ("Bit Manipulation",   ["Bit Manipulation - Basic", "Bit Manipulation - Interview",
                            "Bit Manipulation - Advanced"]),
    ("Stack & Queue",      ["Stack & Queue - Learning", "Stack & Queue - Conversion",
                            "Stack & Queue - Monotonic", "Stack & Queue - Implementation"]),
    ("Sliding Window",     ["Sliding Window - Medium", "Sliding Window - Hard"]),
    ("Heaps",              ["Heaps - Learning", "Heaps - Medium", "Heaps - Hard"]),
    ("Greedy",             ["Greedy - Easy", "Greedy - Medium/Hard"]),
    ("Binary Trees",       ["Binary Trees - Traversals", "Binary Trees - Medium", "Binary Trees - Hard"]),
    ("BST",                ["BST - Concepts", "BST - Problems"]),
    ("Graphs",             ["Graphs - Learning", "Graphs - BFS/DFS", "Graphs - Topo Sort",
                            "Graphs - Shortest Path", "Graphs - MST/DSU", "Graphs - Other"]),
    ("Dynamic Programming",["DP - Introduction", "DP - 1D", "DP - Grids", "DP - Subsequences",
                            "DP - Strings", "DP - Stocks", "DP - LIS", "DP - MCM/Partition",
                            "DP - Squares"]),
    ("Tries",              ["Tries - Theory", "Tries - Problems"]),
])


# ─── Helpers ──────────────────────────────────────────────

def normalize(text):
    """Normalize text for comparison: lowercase, remove all non-alphanumeric."""
    return re.sub(r'[^a-z0-9]', '', text.lower())


def parse_csv():
    """Parse the Striver's A2Z sheet CSV file."""
    problems = []
    with open(CSV_PATH, 'r', encoding='utf-8-sig') as f:
        reader = csv.DictReader(f)
        for row in reader:
            name = row.get('Problem', '').strip()
            if not name:
                continue
            diff = row.get('Difficulty', '').strip().capitalize()
            if diff not in ('Easy', 'Medium', 'Hard'):
                diff = 'Medium'
            problems.append({
                'name':     name,
                'topic':    row.get('Topic', '').strip(),
                'difficulty': diff,
                'pattern':  row.get('Pattern', '').strip(),
                'solved':   False,
                'folder':   '',
                'link':     '',
                'hasNotes': False,
            })
    return problems


def scan_leetcode_folders():
    """Find all numbered LeetCode solution folders in the repo."""
    folders = []
    for entry in sorted(os.scandir(REPO_ROOT), key=lambda e: e.name):
        if entry.is_dir() and re.match(r'^\d{4}-', entry.name):
            name_part = re.sub(r'^\d+-', '', entry.name)

            # Extract LeetCode URL from README
            link = f"https://leetcode.com/problems/{name_part}/"
            readme = Path(entry.path) / "README.md"
            if readme.exists():
                try:
                    content = readme.read_text(encoding='utf-8', errors='ignore')
                    m = re.search(r'href="(https://leetcode\.com/problems/[^"]+)"', content)
                    if m:
                        link = m.group(1)
                except Exception:
                    pass

            folders.append({
                'folder':    entry.name,
                'name_part': name_part,
                'link':      link,
                'has_notes': (Path(entry.path) / "NOTES.md").exists(),
            })
    return folders


def load_stats_shas():
    """Load difficulty data from stats.json."""
    if STATS_PATH.exists():
        try:
            with open(STATS_PATH, 'r', encoding='utf-8') as f:
                data = json.load(f)
            shas = data.get('leetcode', {}).get('shas', data.get('shas', {}))
            return shas if isinstance(shas, dict) else {}
        except Exception:
            pass
    return {}


def match_problems(csv_problems, leetcode_folders):
    """Match LeetCode solution folders to CSV problems.

    Returns (matched_count, list_of_unmatched_folders).
    """
    # Build normalized lookup: norm(csv_name) → index
    csv_lookup = {}
    for i, p in enumerate(csv_problems):
        key = normalize(p['name'])
        if key not in csv_lookup:
            csv_lookup[key] = i

    matched_count = 0
    unmatched = []

    for folder in leetcode_folders:
        name_part = folder['name_part']
        idx = None

        # ── Method 1: Known manual mapping ──
        csv_name = FOLDER_TO_CSV.get(name_part)
        if csv_name:
            key = normalize(csv_name)
            if key in csv_lookup:
                idx = csv_lookup[key]

        # ── Method 2: Normalized direct match ──
        if idx is None:
            folder_norm = normalize(name_part.replace('-', ''))
            if folder_norm in csv_lookup:
                idx = csv_lookup[folder_norm]

        # ── Method 3: Best partial / substring match ──
        if idx is None:
            folder_norm = normalize(name_part.replace('-', ''))
            best_idx, best_score = None, 0.0
            for key, cidx in csv_lookup.items():
                if csv_problems[cidx]['solved']:
                    continue
                if len(folder_norm) >= 4 and len(key) >= 4:
                    if folder_norm in key or key in folder_norm:
                        score = min(len(folder_norm), len(key)) / max(len(folder_norm), len(key))
                        if score > best_score and score > 0.5:
                            best_score = score
                            best_idx = cidx
            idx = best_idx

        # ── Apply match ──
        if idx is not None and not csv_problems[idx]['solved']:
            csv_problems[idx]['solved']   = True
            csv_problems[idx]['folder']   = folder['folder']
            csv_problems[idx]['link']     = folder['link'] or csv_problems[idx]['link']
            csv_problems[idx]['hasNotes'] = folder['has_notes']
            matched_count += 1
        else:
            unmatched.append(folder)

    return matched_count, unmatched


def classify_patterns(csv_problems):
    """Assign each problem to matching canonical patterns."""
    pattern_data = []

    for cfg in PATTERNS_CONFIG:
        p = {
            'id':          cfg['id'],
            'name':        cfg['name'],
            'emoji':       cfg['emoji'],
            'color':       cfg['color'],
            'description': cfg['description'],
            'whenToUse':   cfg['whenToUse'],
            'problems':    [],
            'total':       0,
            'solved':      0,
        }

        for prob in csv_problems:
            pattern_str = prob['pattern'].lower()
            if any(kw in pattern_str for kw in cfg['keywords']):
                p['problems'].append({
                    'name':       prob['name'],
                    'difficulty': prob['difficulty'],
                    'solved':     prob['solved'],
                    'link':       prob['link'],
                    'topic':      prob['topic'],
                })
                p['total'] += 1
                if prob['solved']:
                    p['solved'] += 1

        pattern_data.append(p)

    return pattern_data


def compute_topics(csv_problems):
    """Compute topic-wise progress grouped by main topic."""
    sub_stats = defaultdict(lambda: {'total': 0, 'solved': 0, 'problems': []})
    for p in csv_problems:
        sub_stats[p['topic']]['total'] += 1
        sub_stats[p['topic']]['problems'].append(p)
        if p['solved']:
            sub_stats[p['topic']]['solved'] += 1

    topics = []
    for group_name, subtopics in TOPIC_GROUPS.items():
        group = {'name': group_name, 'total': 0, 'solved': 0, 'subtopics': []}
        for st in subtopics:
            s = sub_stats.get(st, {'total': 0, 'solved': 0, 'problems': []})
            group['subtopics'].append({'name': st, **s})
            group['total']  += s['total']
            group['solved'] += s['solved']
        if group['total'] > 0:
            topics.append(group)

    return topics


def get_commit_dates():
    """Get unique git commit dates for heatmap (dates when .cpp files were added)."""
    try:
        result = subprocess.run(
            ['git', 'log', '--format=%aI', '--diff-filter=A', '--', '*.cpp'],
            cwd=str(REPO_ROOT), capture_output=True, text=True, timeout=30,
        )
        if result.returncode == 0:
            dates = set()
            for line in result.stdout.strip().split('\n'):
                if line:
                    dates.add(line[:10])   # YYYY-MM-DD
            return sorted(dates)
    except Exception:
        pass
    return []


def generate_data_js(data):
    """Write dashboard/data.js with the computed data."""
    DATA_JS_PATH.parent.mkdir(parents=True, exist_ok=True)

    content  = "// Auto-generated by scripts/sync.py — DO NOT EDIT MANUALLY\n"
    content += f"// Last synced: {data['meta']['lastSynced']}\n\n"
    content += "const DSA_DATA = "
    content += json.dumps(data, indent=2, ensure_ascii=False)
    content += ";\n"

    DATA_JS_PATH.write_text(content, encoding='utf-8')


def update_readme(patterns, topics):
    """Inject dynamically generated markdown into README.md."""
    readme_path = REPO_ROOT / "README.md"
    if not readme_path.exists():
        return

    content = readme_path.read_text(encoding='utf-8')

    # 1. Generate Patterns Markdown
    pat_md = []
    for p in patterns:
        pat_md.append(f"### {p['id']}. {p['emoji']} {p['name']}")
        pat_md.append(f"> **When:** {p['whenToUse']}")
        pat_md.append(">")
        if p['solved'] > 0:
            pat_md.append("> | Problem | Difficulty | Solution |")
            pat_md.append("> |---------|------------|----------|")
            for prob in p['problems']:
                if prob['solved']:
                    folder_link = f"[Code](./{prob['folder']})" if 'folder' in prob and prob['folder'] else "✅"
                    pat_md.append(f"> | [{prob['name']}]({prob['link']}) | {prob['difficulty']} | {folder_link} |")
        else:
            pat_md.append("> *No problems solved yet for this pattern.*")
        pat_md.append("\n")

    pat_str = "\n".join(pat_md)
    content = re.sub(r'<!-- PATTERNS_START -->.*?<!-- PATTERNS_END -->',
                     f'<!-- PATTERNS_START -->\n{pat_str}\n<!-- PATTERNS_END -->',
                     content, flags=re.DOTALL)

    # 2. Generate Topics Markdown
    top_md = []
    top_md.append("| Topic | Solved | Total | Progress |")
    top_md.append("|-------|--------|-------|----------|")
    for t in topics:
        pct = t['solved'] / max(t['total'], 1) * 100
        bars = int(pct / 20)
        progress = "🟩" * bars + "⬜" * (5 - bars)
        status = "✅" if t['solved'] == t['total'] else ("⏳" if t['solved'] > 0 else "⬜")
        top_md.append(f"| **{t['name']}** | {status} | {t['solved']}/{t['total']} | {progress} |")
        
        # Add a collapsible section for solved problems under this group if any
        solved_probs = []
        for st in t['subtopics']:
            if st.get('problems'):
                for p in st['problems']:
                    if p['solved']:
                        solved_probs.append(p)
                        
        if solved_probs:
            top_md.append(f"| <details><summary>View {len(solved_probs)} Solved</summary><ul>" + "".join([f"<li>[{p['name']}]({p['link']}) - [Code](./{p['folder']})</li>" for p in solved_probs]) + "</ul></details> | | | |")

    top_str = "\n".join(top_md)
    content = re.sub(r'<!-- TOPICS_START -->.*?<!-- TOPICS_END -->',
                     f'<!-- TOPICS_START -->\n{top_str}\n<!-- TOPICS_END -->',
                     content, flags=re.DOTALL)

    readme_path.write_text(content, encoding='utf-8')


# ─── Main ─────────────────────────────────────────────────

def main():
    print("\n🔄  Syncing a2Z_DSA repository …\n")

    # 1. Parse CSV
    csv_problems = parse_csv()
    print(f"  📖  Parsed CSV: {len(csv_problems)} problems")

    # 2. Load stats for difficulty info
    stats_shas = load_stats_shas()

    # 3. Scan solution folders
    leetcode_folders = scan_leetcode_folders()
    print(f"  📂  Solution folders: {len(leetcode_folders)}")

    # 4. Match
    matched, unmatched = match_problems(csv_problems, leetcode_folders)
    print(f"  🔗  Matched to A2Z sheet: {matched}/{len(leetcode_folders)}")
    if unmatched:
        print(f"  ℹ️   Bonus (not in sheet): {len(unmatched)}")
        for u in unmatched:
            print(f"       • {u['folder']}")

    # 5. Difficulty breakdown
    diff = {'Easy': {'total': 0, 'solved': 0},
            'Medium': {'total': 0, 'solved': 0},
            'Hard': {'total': 0, 'solved': 0}}
    for p in csv_problems:
        d = p['difficulty']
        if d in diff:
            diff[d]['total'] += 1
            if p['solved']:
                diff[d]['solved'] += 1

    total_solved = sum(1 for p in csv_problems if p['solved']) + len(unmatched)
    pct = round(total_solved / max(len(csv_problems), 1) * 100, 1)

    print(f"\n  📊  Progress: {total_solved}/{len(csv_problems)} ({pct}%)")
    for d in ('Easy', 'Medium', 'Hard'):
        print(f"       {d}: {diff[d]['solved']}/{diff[d]['total']}")

    # 6. Patterns
    patterns = classify_patterns(csv_problems)
    active = sum(1 for p in patterns if p['solved'] > 0)
    print(f"  🧩  Patterns active: {active}/28")

    # 7. Topics
    topics = compute_topics(csv_problems)

    # 8. Commit dates
    commit_dates = get_commit_dates()
    print(f"  📅  Commit dates: {len(commit_dates)} unique days")

    # 9. Assemble data
    data = {
        'meta': {
            'lastSynced': datetime.now().isoformat(),
            'repoUrl': 'https://github.com/gitkrypton18/a2Z_DSA',
        },
        'summary': {
            'total': len(csv_problems),
            'solved': total_solved,
            'percentage': pct,
            'difficulty': {
                'easy':   diff['Easy'],
                'medium': diff['Medium'],
                'hard':   diff['Hard'],
            },
        },
        'patterns': patterns,
        'topics':   topics,
        'problems': [{
            'name':       p['name'],
            'topic':      p['topic'],
            'difficulty': p['difficulty'],
            'pattern':    p['pattern'],
            'solved':     p['solved'],
            'folder':     p['folder'],
            'link':       p['link'],
            'hasNotes':   p['hasNotes'],
        } for p in csv_problems],
        'bonusProblems': [{
            'folder':   u['folder'],
            'link':     u['link'],
            'hasNotes': u['has_notes'],
        } for u in unmatched],
        'commitDates': commit_dates,
    }

    # 10. Write data.js
    generate_data_js(data)
    print(f"\n  ✅  Generated dashboard/data.js")

    # 11. Update stats.json
    enhanced = {
        'leetcode': {
            'easy':    diff['Easy']['solved'],
            'medium':  diff['Medium']['solved'],
            'hard':    diff['Hard']['solved'],
            'solved':  total_solved,
            'total':   len(csv_problems),
            'shas':    stats_shas,
        },
        'patterns_active': active,
        'topics_covered':  sum(1 for t in topics if t['solved'] > 0),
    }
    STATS_PATH.write_text(json.dumps(enhanced, indent=2), encoding='utf-8')
    print(f"  ✅  Updated stats.json")

    # 12. Update README
    update_readme(patterns, topics)
    print(f"  ✅  Updated README.md")

    print(f"\n  ✨  Sync complete! Open dashboard/index.html to view your progress.\n")


if __name__ == '__main__':
    main()
