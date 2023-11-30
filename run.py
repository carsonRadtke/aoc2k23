#!/usr/bin/env python3

import sys
import os

def read_compile_flags(compile_flags_txt: str) -> list[str]: 
  with open(compile_flags_txt, 'r') as cff:
    return [line for line in map(lambda x: x.strip(), cff.readlines()) if len(line) > 0]

def find_root() -> str:
  return os.path.dirname(__file__)

def usage():
  return f"usage: {sys.argv[0]} <src_file> <input_file>"

def build_compiler_command(root: str, src: str, binary: str) -> str:
  return ['clang++', src, '-o', binary] + read_compile_flags(f"{root}/compile_flags.txt")

def build_and_run(command: str, inp: str, binary: str) -> int:
  for cmd in [" ".join(command), f"{binary} {inp}"]:
    print(f">> {cmd}")
    rv = os.system(cmd)
    if (rv != 0):
      return 1
  return 0

def run_main(src: str, inp: str) -> int:
  root = find_root()
  binary = src.replace(src[src.rindex("."):], "").replace("src", "bin")
  compiler_command = build_compiler_command(root, src, binary)
  return build_and_run(compiler_command, inp, binary)

def main(argv: list[str]) -> int:
  assert len(argv) == 2, usage()
  [source_file, input_file] = argv
  return run_main(source_file, input_file)

if __name__ == '__main__':
  sys.exit(main(sys.argv[1:]))
