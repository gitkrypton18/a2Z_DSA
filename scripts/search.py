#!/usr/bin/env python3
"""
search.py — CLI search & filter tool for a2Z_DSA problems.

Usage examples:
    python scripts/search.py --pattern "Two Pointers"
    python scripts/search.py --difficulty hard --solved
    python scripts/search.py --topic "Binary Search"
    python scripts/search.py --unsolved --difficulty easy
    python scripts/search.py --query "sum"
    python scripts/search.py --list-patterns
    python scripts/search.py --stats
"""

import argparse
import csv
import json
import os
import re
import sys
from pathlib import Path
from collections import defaultdict

REPO_ROOT = Path(__file__).resolve().parent.parent
CSV_PATH = REPO_ROOT / "Strivers_A2Z_Sheet_with_Patterns.csv"
STATS_PATH = REPO_ROOT / "stats.json"
DATA_JS_PATH = REPO_ROOT / "dashboard" / "data.js"

# ─── ANSI Colors ──────────────────────────────────────────
GREEN  = '\033[92m'
YELLOW = '\033[93m'
RED    = '\033[91m'
CYAN   = '\033[96m'
MAGENTA= '\033[95m'
BOLD   = '\033[1m'
DIM    = '\033[2m'
RESET  = '\033[0m'

DIFF_COLORS = {'Easy': GREEN, 'Medium': YELLOW, 'Hard': RED}

# Use the same mappings as sync.py for matching
FOLDER_TO_CSV = {
    "maximum-subarray": "Kadane's Algorithm",
    "sort-colors": "Sort array of 0's 1's and 2's",
    "best-time-to-buy-and-sell-stock": "Stock Buy and Sell",
    "spiral-matrix": "Print matrix in spiral manner",
    "rotate-image": "Rotate matrix by 90 degrees",
    "single-number": "Find number that appears once (others twice)",
    "max-consecutive-ones": "Maximum Consecutive Ones",
    "majority-element": "Majority Element-I",
    "majority-element-ii": "Majority Element-II",
    "subarray-sum-equals-k": "Count subarrays with given sum",
    "merge-sorted-array": "Merge two sorted arrays without extra space",
    "binary-search": "Search X in sorted array",
    "reverse-integer": "Reverse a number",
    "palindrome-number": "Check Palindrome",
    "sqrtx": "Find square root of a number",
    "power-of-two": "Check if Number is Power of 2",
    "valid-anagram": "Check if two strings are anagram",
    "valid-palindrome": "Check Palindrome",
    "rotate-array": "Left Rotate Array by K Places",
    "sort-an-array": "Merge Sort",
    "merge-intervals": "Merge Overlapping Subintervals",
    "pascals-triangle": "Pascal's Triangle I",
    "find-missing-and-repeated-values": "Find repeating and missing number",
    "fibonacci-number": "N-th Fibonacci number",
    "magnetic-force-between-two-balls": "Aggressive Cows",
    "median-of-two-sorted-arrays": "Median of 2 sorted arrays",
    "3sum": "3 Sum", "4sum": "4 Sum",
    "isomorphic-strings": "Isomorphic String",
    "check-if-array-is-sorted-and-rotated": "Check if Array is Sorted",
    "minimum-number-of-days-to-make-m-bouquets": "Minimum days to make M bouquets",
    "find-first-and-last-position-of-element-in-sorted-array": "First and last occurrence",
    "search-in-rotated-sorted-array-ii": "Search in rotated sorted array-II",
    "find-minimum-in-rotated-sorted-array": "Find minimum in Rotated Sorted Array",
    "single-element-in-a-sorted-array": "Single element in Sorted Array",
    "find-peak-element": "Find peak element",
    "maximum-product-subarray": "Maximum Product Subarray",
    "search-insert-position": "Search insert position",
    "search-a-2d-matrix": "Search in a 2D matrix",
    "search-a-2d-matrix-ii": "Search in 2D matrix - II",
    "find-a-peak-element-ii": "Find Peak Element - II",
    "remove-outermost-parentheses": "Remove Outermost Parentheses",
    "largest-odd-number-in-string": "Largest Odd Number in a String",
    "longest-common-prefix": "Longest Common Prefix",
    "sort-characters-by-frequency": "Sort Characters by Frequency",
    "maximum-nesting-depth-of-the-parentheses": "Maximum Nesting Depth of Parentheses",
    "sum-of-beauty-of-all-substrings": "Sum of Beauty of All Substrings",
    "rearrange-array-elements-by-sign": "Rearrange array elements by sign",
    "reverse-pairs": "Reverse Pairs",
    "set-matrix-zeroes": "Set Matrix Zeroes",
    "longest-consecutive-sequence": "Longest Consecutive Sequence",
    "remove-duplicates-from-sorted-array": "Remove duplicates from Sorted array",
    "move-zeroes": "Move Zeros to End",
    "next-permutation": "Next Permutation",
    "rotate-string": "Rotate String",
    "capacity-to-ship-packages-within-d-days": "Capacity to Ship Packages Within D Days",
    "kth-missing-positive-number": "Kth Missing Positive Number",
    "find-the-smallest-divisor-given-a-threshold": "Find the smallest divisor",
    "split-array-largest-sum": "Split array - largest sum",
}

# Reverse mapping: CSV name → folder
CSV_TO_FOLDER = {v: k for k, v in FOLDER_TO_CSV.items()}


def normalize(text):
    return re.sub(r'[^a-z0-9]', '', text.lower())


def load_problems():
    """Load all problems from CSV with solved status."""
    # Get solved folders
    solved_folders = set()
    for entry in os.scandir(REPO_ROOT):
        if entry.is_dir() and re.match(r'^\d{4}-', entry.name):
            solved_folders.add(entry.name)

    # Build reverse lookup: norm(csv_name) → solved
    solved_csv_names = set()
    for folder in solved_folders:
        name_part = re.sub(r'^\d+-', '', folder)
        # Check known mapping
        csv_name = FOLDER_TO_CSV.get(name_part)
        if csv_name:
            solved_csv_names.add(normalize(csv_name))
        # Also add normalized folder name
        solved_csv_names.add(normalize(name_part.replace('-', '')))

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
            is_solved = normalize(name) in solved_csv_names
            problems.append({
                'name':       name,
                'topic':      row.get('Topic', '').strip(),
                'difficulty': diff,
                'pattern':    row.get('Pattern', '').strip(),
                'solved':     is_solved,
            })
    return problems


def display_table(results):
    """Pretty-print results as a table."""
    if not results:
        print(f"\n  {DIM}No problems found matching your criteria.{RESET}\n")
        return

    print(f"\n  {BOLD}Found {len(results)} problem(s):{RESET}\n")

    # Header
    print(f"  {BOLD}{'#':<4} {'Problem':<48} {'Diff':<10} {'Topic':<28} {'Pattern':<32} {'Status':<6}{RESET}")
    print(f"  {'─'*130}")

    for i, p in enumerate(results, 1):
        dc = DIFF_COLORS.get(p['difficulty'], '')
        status = f"{GREEN}✅{RESET}" if p['solved'] else f"{DIM}⬜{RESET}"
        pname = p['name'][:46] + '..' if len(p['name']) > 48 else p['name']
        topic = p['topic'][:26] + '..' if len(p['topic']) > 28 else p['topic']
        pat   = p['pattern'][:30] + '..' if len(p['pattern']) > 32 else p['pattern']
        print(f"  {i:<4} {pname:<48} {dc}{p['difficulty']:<10}{RESET} {topic:<28} {CYAN}{pat:<32}{RESET} {status}")

    print()
    solved_n = sum(1 for p in results if p['solved'])
    print(f"  {BOLD}Summary:{RESET} {GREEN}{solved_n} solved{RESET} / {len(results)} total")
    print()


def show_stats(problems):
    """Show overall statistics."""
    total = len(problems)
    solved = sum(1 for p in problems if p['solved'])

    # Difficulty
    diff_stats = defaultdict(lambda: {'total': 0, 'solved': 0})
    for p in problems:
        diff_stats[p['difficulty']]['total'] += 1
        if p['solved']:
            diff_stats[p['difficulty']]['solved'] += 1

    # Topics
    topic_stats = defaultdict(lambda: {'total': 0, 'solved': 0})
    for p in problems:
        topic_stats[p['topic']]['total'] += 1
        if p['solved']:
            topic_stats[p['topic']]['solved'] += 1

    # Patterns
    pattern_set = set()
    for p in problems:
        for pat in p['pattern'].split('/'):
            pat = pat.strip()
            if pat:
                pattern_set.add(pat)

    print(f"\n  {BOLD}📊 a2Z_DSA Statistics{RESET}")
    print(f"  {'─'*50}")
    print(f"  Total Problems:  {BOLD}{total}{RESET}")
    print(f"  Solved:          {GREEN}{BOLD}{solved}{RESET} ({solved/total*100:.1f}%)")
    print(f"  Remaining:       {YELLOW}{total - solved}{RESET}")
    print()

    print(f"  {BOLD}Difficulty Breakdown:{RESET}")
    for d in ('Easy', 'Medium', 'Hard'):
        s = diff_stats[d]
        dc = DIFF_COLORS.get(d, '')
        bar_len = int(s['solved'] / max(s['total'], 1) * 20)
        bar = '█' * bar_len + '░' * (20 - bar_len)
        print(f"    {dc}{d:<8}{RESET} {bar} {s['solved']}/{s['total']}")
    print()

    print(f"  {BOLD}Top 10 Topics by Completion:{RESET}")
    sorted_topics = sorted(topic_stats.items(), key=lambda x: x[1]['solved'], reverse=True)
    for name, s in sorted_topics[:10]:
        pct = s['solved'] / max(s['total'], 1) * 100
        bar_len = int(pct / 5)
        bar = '█' * bar_len + '░' * (20 - bar_len)
        print(f"    {name:<35} {bar} {s['solved']}/{s['total']} ({pct:.0f}%)")
    print()


def list_patterns(problems):
    """List all unique patterns with counts."""
    pattern_counts = defaultdict(lambda: {'total': 0, 'solved': 0})
    for p in problems:
        for pat in p['pattern'].split('/'):
            pat = pat.strip()
            if pat and pat not in ('Basic', 'Brute Force', 'Basic / Brute Force'):
                pattern_counts[pat]['total'] += 1
                if p['solved']:
                    pattern_counts[pat]['solved'] += 1

    print(f"\n  {BOLD}🧩 All DSA Patterns ({len(pattern_counts)} unique):{RESET}\n")
    for name, s in sorted(pattern_counts.items(), key=lambda x: x[1]['total'], reverse=True):
        pct = s['solved'] / max(s['total'], 1) * 100
        dc = GREEN if pct > 50 else (YELLOW if pct > 0 else DIM)
        print(f"    {dc}{'●':<2}{RESET} {name:<40} {s['solved']}/{s['total']} ({pct:.0f}%)")
    print()


def list_topics(problems):
    """List all topics with progress."""
    topic_stats = defaultdict(lambda: {'total': 0, 'solved': 0})
    for p in problems:
        topic_stats[p['topic']]['total'] += 1
        if p['solved']:
            topic_stats[p['topic']]['solved'] += 1

    print(f"\n  {BOLD}📚 All Topics:{RESET}\n")
    for name, s in sorted(topic_stats.items()):
        pct = s['solved'] / max(s['total'], 1) * 100
        dc = GREEN if pct > 50 else (YELLOW if pct > 0 else DIM)
        bar_len = int(pct / 5)
        bar = '█' * bar_len + '░' * (20 - bar_len)
        print(f"    {dc}{name:<40}{RESET} {bar} {s['solved']}/{s['total']}")
    print()


def main():
    parser = argparse.ArgumentParser(
        description="🔍 Search & filter a2Z_DSA problems",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python scripts/search.py --pattern "Two Pointers"
  python scripts/search.py --difficulty hard --solved
  python scripts/search.py --topic "Arrays"
  python scripts/search.py --unsolved --difficulty easy
  python scripts/search.py --query "palindrome"
  python scripts/search.py --list-patterns
  python scripts/search.py --stats
        """,
    )
    parser.add_argument('-p', '--pattern',  help='Filter by pattern (substring match)')
    parser.add_argument('-d', '--difficulty', choices=['easy', 'medium', 'hard'],
                        help='Filter by difficulty')
    parser.add_argument('-t', '--topic',    help='Filter by topic (substring match)')
    parser.add_argument('-q', '--query',    help='Search by problem name keyword')
    parser.add_argument('--solved',         action='store_true', help='Only solved')
    parser.add_argument('--unsolved',       action='store_true', help='Only unsolved')
    parser.add_argument('--list-patterns',  action='store_true', help='List all patterns')
    parser.add_argument('--list-topics',    action='store_true', help='List all topics')
    parser.add_argument('--stats',          action='store_true', help='Overall statistics')

    args = parser.parse_args()
    problems = load_problems()

    # Special commands
    if args.stats:
        show_stats(problems)
        return
    if args.list_patterns:
        list_patterns(problems)
        return
    if args.list_topics:
        list_topics(problems)
        return

    # Apply filters
    results = problems
    if args.pattern:
        results = [p for p in results if args.pattern.lower() in p['pattern'].lower()]
    if args.difficulty:
        results = [p for p in results if p['difficulty'].lower() == args.difficulty.lower()]
    if args.topic:
        results = [p for p in results if args.topic.lower() in p['topic'].lower()]
    if args.query:
        results = [p for p in results if args.query.lower() in p['name'].lower()]
    if args.solved:
        results = [p for p in results if p['solved']]
    if args.unsolved:
        results = [p for p in results if not p['solved']]

    # Default: show all if no filters
    if not any([args.pattern, args.difficulty, args.topic, args.query, args.solved, args.unsolved]):
        show_stats(problems)
        return

    display_table(results)


if __name__ == '__main__':
    main()
