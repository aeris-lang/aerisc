import os
from util.shell import cmd

def main() -> None:
    os.makedirs("out", exist_ok = True)
    os.makedirs("out/tmp", exist_ok = True)
    cmd("clang -c src/main.c -o out/tmp/main.o")
    cmd("clang out/tmp/main.o -o out/aerisc")
    return

if __name__ == '__main__': main()