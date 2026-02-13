import os
import json
import sys

snippets = {}

for subdir in os.walk('.'):
  if '.git' in subdir[0]:
    continue
  print(subdir)
  for filename in subdir[2]:
    name, extension = filename.split('.')
  # for name in subdir[2]:
    # if '.' in name:
    if extension not in ("cpp", "py"):
      continue

    if name in snippets:
      print(f'error: duplicate snippet {name}', file=sys.stderr)
      exit(0)

    path = subdir[0] + '/' + filename
    with open(path, 'r') as f:
      snippet = {
        "prefix": name,
        "body": [line.rstrip() for line in f.readlines()],
        "description": name
      }
      snippets[name] = snippet

    print(f'generated snippet {name}', file=sys.stderr)

with open('cpp.code-snippets', 'w') as f:
  f.write(json.dumps(snippets, indent=2))

print('done', file=sys.stderr)