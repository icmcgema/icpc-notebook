#! /usr/bin/env python3

from pathlib import Path
import argparse
import re, os
from contextlib import redirect_stdout

parser = argparse.ArgumentParser()
parser.add_argument("readme_file")
parser.add_argument("root_dir")
parser.add_argument("-o", "--out_file", metavar="out_file")
args = parser.parse_args()

root_dir = Path(args.root_dir).resolve()
readme_file = Path(args.readme_file).resolve()

def get_files(root_dir):
    fs = []
    for path, subdirs, files in os.walk(root_dir):
        for name in files:
            fs.append(str(Path(path, name).relative_to(root_dir)))
    return fs

def updated_readme(readme_file, root_dir):
    files = get_files(root_dir)
    in_todo = False

    with open(readme_file) as f:
        for line in f:
            line = line.rstrip('\n ')
            
            if match := re.search(r"^[#]+\s*(.+)", line):
                text = match.group(1)
                in_todo = (text == "Todo")
                print(line)
                continue

            if not in_todo:
                print(line)
                continue

            if match := re.search(r"(\s*[-]+\s*)([A-Za-z0-9.]+)([^\n]*)", line):
                prev_space, file, after_space = (match.groups())

                dirs = list(filter(lambda x: "/"+file in x, files))
                
                if not dirs:
                    print(line)
                    continue
                
                link = dirs[0]
                print('{}[{}]({}){}'.format(prev_space, file, link, after_space))

            else:
                print(line)

if args.out_file:
    with open(args.out_file, "w+") as f:
        with redirect_stdout(f):
            updated_readme(readme_file, root_dir)
else:
    updated_readme(readme_file, root_dir)