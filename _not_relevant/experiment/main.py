import sys
from collections import defaultdict

def parse_log_entry(line):
    parts = line.split()
    if len(parts) < 4 or len(parts) % 2 != 0:
        return None
    entry = {}
    try:
        entry['id'] = int(parts[1])
        entry['timestamp'] = int(parts[3])
        for i in range(4, len(parts), 2):
            entry[parts[i]] = parts[i + 1]
    except ValueError:
        return None
    return entry

def main():
    input = sys.stdin.read().strip().split('\n')
    N = int(input[0])
    log_entries = []
    file_to_commits = defaultdict(list)
    commit_to_files = {}
    ambiguous = False

    for i in range(1, N + 1):
        entry = parse_log_entry(input[i])
        if entry:
            log_entries.append(entry)
            commit_id = entry['id']
            commit_to_files[commit_id] = entry
            for file_path, opaque_id in entry.items():
                if file_path not in ['id', 'timestamp']:
                    file_to_commits[(file_path, opaque_id)].append(commit_id)
        else:
            continue

    # Check for ambiguity
    for file_path, commits in file_to_commits.items():
        if len(commits) > 1:
            for i in range(len(commits)):
                for j in range(i + 1, len(commits)):
                    commit_i = commit_to_files[commits[i]]
                    commit_j = commit_to_files[commits[j]]
                    common_files = set(commit_i.keys()).intersection(set(commit_j.keys()))
                    for file in common_files:
                        if file not in ['id', 'timestamp'] and commit_i[file] != commit_j[file]:
                            ambiguous = True
                            break
                if ambiguous:
                    break
        if ambiguous:
            break

    if ambiguous:
        print("AMBIGUOUS INPUT!")
        return

    R = int(input[N + 1])
    queries = input[N + 2:N + 2 + R]

    for query in queries:
        start_ts, end_ts, file_path, opaque_id = query.split()
        start_ts = int(start_ts)
        end_ts = int(end_ts)
        result = []

        if (file_path, opaque_id) in file_to_commits:
            for commit_id in file_to_commits[(file_path, opaque_id)]:
                commit = commit_to_files[commit_id]
                if start_ts <= commit['timestamp'] <= end_ts:
                    result.append((commit['timestamp'], commit_id))

        result.sort()
        print(" ".join(str(commit_id) for _, commit_id in result))

if __name__ == "__main__":
    main()