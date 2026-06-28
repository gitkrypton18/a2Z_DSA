#!/usr/bin/env python3
"""
generate_notes.py — Generate NOTES.md stubs for all solved LeetCode problems.

Reads the NOTES_TEMPLATE.md template and fills in problem info from CSV/stats.

Usage:
    python scripts/generate_notes.py           # Skip existing NOTES.md
    python scripts/generate_notes.py --force   # Overwrite all NOTES.md
"""

import argparse
import csv
import json
import os
import re
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
TEMPLATE_PATH = REPO_ROOT / "templates" / "NOTES_TEMPLATE.md"
CSV_PATH = REPO_ROOT / "Strivers_A2Z_Sheet_with_Patterns.csv"
STATS_PATH = REPO_ROOT / "stats.json"

# Same mapping as sync.py — maps LeetCode folder slug → CSV problem name
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
    "add-digits": "Sum of all divisors",
    "xor-operation-in-an-array": "XOR of numbers in given range",
    "integer-to-roman": "Roman to Integer",
}


def normalize(text):
    return re.sub(r'[^a-z0-9]', '', text.lower())


def load_csv_lookup():
    """Build lookup: normalized_name → {name, topic, difficulty, pattern}."""
    lookup = {}
    with open(CSV_PATH, 'r', encoding='utf-8-sig') as f:
        reader = csv.DictReader(f)
        for row in reader:
            name = row.get('Problem', '').strip()
            if not name:
                continue
            diff = row.get('Difficulty', '').strip().capitalize()
            if diff not in ('Easy', 'Medium', 'Hard'):
                diff = 'Medium'
            lookup[normalize(name)] = {
                'name':       name,
                'topic':      row.get('Topic', '').strip(),
                'difficulty': diff,
                'pattern':    row.get('Pattern', '').strip(),
            }
    return lookup


def find_csv_info(folder_name, csv_lookup):
    """Find CSV metadata for a given LeetCode folder."""
    name_part = re.sub(r'^\d+-', '', folder_name)

    # Known mapping
    csv_name = FOLDER_TO_CSV.get(name_part)
    if csv_name:
        key = normalize(csv_name)
        if key in csv_lookup:
            return csv_lookup[key]

    # Normalized match
    key = normalize(name_part.replace('-', ''))
    if key in csv_lookup:
        return csv_lookup[key]

    # Partial match
    for k, v in csv_lookup.items():
        if len(key) >= 4 and (key in k or k in key):
            return v

    return None


def main():
    parser = argparse.ArgumentParser(description="📝 Generate NOTES.md stubs for solved problems")
    parser.add_argument('--force', action='store_true', help='Overwrite existing NOTES.md files')
    args = parser.parse_args()

    # Load template
    if not TEMPLATE_PATH.exists():
        print(f"  ❌ Template not found: {TEMPLATE_PATH}")
        return
    template = TEMPLATE_PATH.read_text(encoding='utf-8')

    # Load CSV lookup
    csv_lookup = load_csv_lookup()

    # Load stats for fallback difficulty
    stats_shas = {}
    if STATS_PATH.exists():
        try:
            with open(STATS_PATH, 'r', encoding='utf-8') as f:
                data = json.load(f)
            stats_shas = data.get('leetcode', {}).get('shas', {})
        except Exception:
            pass

    created = 0
    skipped = 0

    print(f"\n📝  Generating NOTES.md stubs …\n")

    for entry in sorted(os.scandir(REPO_ROOT), key=lambda e: e.name):
        if not entry.is_dir() or not re.match(r'^\d{4}-', entry.name):
            continue

        notes_path = Path(entry.path) / "NOTES.md"
        if notes_path.exists() and not args.force:
            skipped += 1
            continue

        name_part = re.sub(r'^\d+-', '', entry.name)
        info = find_csv_info(entry.name, csv_lookup)

        problem_name = info['name']       if info else name_part.replace('-', ' ').title()
        difficulty   = info['difficulty']  if info else 'Medium'
        pattern      = info['pattern']     if info else 'Unknown'
        topic        = info['topic']       if info else 'Unknown'
        link         = f"https://leetcode.com/problems/{name_part}/"

        # Fallback difficulty from stats
        folder_data = stats_shas.get(entry.name, {})
        if isinstance(folder_data, dict) and 'difficulty' in folder_data:
            difficulty = folder_data['difficulty'].capitalize()

        # Fill template
        content = template
        content = content.replace('{{PROBLEM_NAME}}', problem_name)
        content = content.replace('{{DIFFICULTY}}',    difficulty)
        content = content.replace('{{PATTERN}}',       pattern)
        content = content.replace('{{TOPIC}}',         topic)
        content = content.replace('{{LINK}}',          link)

        notes_path.write_text(content, encoding='utf-8')
        created += 1
        print(f"  ✅  {entry.name}/NOTES.md")

    print(f"\n📝  Notes generation complete!")
    print(f"    Created:  {created}")
    print(f"    Skipped:  {skipped} (already exist — use --force to overwrite)")
    print()


if __name__ == '__main__':
    main()
