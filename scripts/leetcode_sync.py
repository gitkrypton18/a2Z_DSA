import os
import sys
import json
import time
import urllib.request
from pathlib import Path

# Try to load dotenv if available
try:
    import dotenv
    dotenv.load_dotenv(Path(__file__).parent.parent / '.env')
except ImportError:
    pass

REPO_ROOT = Path(__file__).parent.parent

USERNAME = os.environ.get("LEETCODE_USERNAME", "krypton_18")
SESSION = os.environ.get("LEETCODE_SESSION")
CSRF = os.environ.get("LEETCODE_CSRF_TOKEN")

if not SESSION:
    print("❌ Error: LEETCODE_SESSION is not set in .env file.")
    print("Please check .env.example, create a .env file, and add your cookies.")
    sys.exit(1)

HEADERS = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36',
    'Cookie': f'LEETCODE_SESSION={SESSION}; csrftoken={CSRF};',
    'x-csrftoken': CSRF,
    'Content-Type': 'application/json'
}

LANG_MAP = {
    'cpp': 'cpp',
    'python3': 'py',
    'python': 'py',
    'java': 'java',
    'javascript': 'js',
    'typescript': 'ts',
    'c': 'c',
    'csharp': 'cs'
}

def get_problem_map():
    """Fetch mapping of problem titleSlug -> frontend_question_id"""
    print("Fetching problem list...")
    req = urllib.request.Request('https://leetcode.com/api/problems/algorithms/', headers=HEADERS)
    with urllib.request.urlopen(req) as res:
        data = json.loads(res.read())
        mapping = {}
        for p in data['stat_status_pairs']:
            mapping[p['stat']['question__title_slug']] = {
                'id': p['stat']['frontend_question_id'],
                'title': p['stat']['question__title']
            }
        return mapping

def download_submissions(problem_map):
    """Download all accepted submissions"""
    offset = 0
    limit = 20
    has_next = True
    downloaded = set()
    
    print("\nDownloading submissions...")
    
    while has_next:
        url = f"https://leetcode.com/api/submissions/?offset={offset}&limit={limit}"
        req = urllib.request.Request(url, headers=HEADERS)
        try:
            with urllib.request.urlopen(req) as res:
                data = json.loads(res.read())
                
                for sub in data.get('submissions_dump', []):
                    if sub['status_display'] != 'Accepted':
                        continue
                        
                    slug = sub['title_slug']
                    lang = sub['lang']
                    
                    # Only download the first accepted solution per problem-language combo
                    key = f"{slug}-{lang}"
                    if key in downloaded:
                        continue
                        
                    downloaded.add(key)
                    
                    p_info = problem_map.get(slug)
                    if not p_info:
                        continue
                        
                    p_id = p_info['id']
                    folder_name = f"{p_id:04d}-{slug}"
                    folder_path = REPO_ROOT / folder_name
                    folder_path.mkdir(exist_ok=True)
                    
                    ext = LANG_MAP.get(lang, lang)
                    code_path = folder_path / f"{folder_name}.{ext}"
                    
                    if not code_path.exists():
                        code_path.write_text(sub['code'], encoding='utf-8')
                        print(f"  ✅ Saved {folder_name}.{ext}")
                        
                        # Generate README
                        readme_path = folder_path / "README.md"
                        if not readme_path.exists():
                            readme_path.write_text(f"# {p_info['title']}\n\n[LeetCode Link](https://leetcode.com/problems/{slug}/)", encoding='utf-8')
                            
                has_next = data.get('has_next', False)
                offset += limit
                time.sleep(1) # Be nice to LeetCode API
                
        except Exception as e:
            print(f"Error fetching submissions: {e}")
            break
            
def fetch_heatmap():
    """Fetch user's official LeetCode heatmap calendar"""
    print("\nFetching official LeetCode Heatmap...")
    query = {
        "query": "\n    query userProfileCalendar($username: String!, $year: Int) {\n  matchedUser(username: $username) {\n    userCalendar(year: $year) {\n      activeYears\n      streak\n      totalActiveDays\n      dccBadges {\n        timestamp\n        badge {\n          name\n          icon\n        }\n      }\n      submissionCalendar\n    }\n  }\n}\n    ",
        "variables": {"username": USERNAME}
    }
    
    req = urllib.request.Request(
        'https://leetcode.com/graphql', 
        data=json.dumps(query).encode('utf-8'),
        headers=HEADERS,
        method='POST'
    )
    
    try:
        with urllib.request.urlopen(req) as res:
            data = json.loads(res.read())
            calendar = data['data']['matchedUser']['userCalendar']['submissionCalendar']
            
            # Save it to stats.json
            stats_file = REPO_ROOT / 'stats.json'
            if stats_file.exists():
                stats = json.loads(stats_file.read_text(encoding='utf-8'))
            else:
                stats = {}
                
            stats['leetcode_heatmap'] = json.loads(calendar)
            stats_file.write_text(json.dumps(stats, indent=2), encoding='utf-8')
            print("  ✅ Heatmap data saved to stats.json")
            
    except Exception as e:
        print(f"Error fetching heatmap: {e}")

def main():
    print(f"🚀 Starting LeetCode Full Sync for {USERNAME}")
    p_map = get_problem_map()
    download_submissions(p_map)
    fetch_heatmap()
    print("\n🎉 Sync Complete! You can now run `python scripts/sync.py` to update your dashboard.")

if __name__ == "__main__":
    main()
