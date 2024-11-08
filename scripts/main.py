import os
from typing import List
from util import shell

def build() -> None:
    os.makedirs("out", exist_ok = True)
    os.makedirs("out/tmp", exist_ok = True)
    shell.cmd("clang -c src/main.c -o out/tmp/main.o")
    shell.cmd("clang out/tmp/main.o -o out/aerisc")
    return

def acquireArgs(args:List[str] = []) -> List[str]:
    shell.clear()
    userInput:str = input (
        f"Current: {args}\n"
        "Leave empty to run\n"
        "Argument: "
    )
    args.append(userInput)
    return acquireArgs(args) if userInput else args

def run() -> None:
    cmd:str = "./out/aerisc"
    for arg in acquireArgs():
        cmd += " " + arg
    shell.clear()
    print(shell.cmd(cmd))
    return

def main() -> None:
    userInput:str = input (
        "0: Exit\n"
        "1: Build\n"
        "2: Run Last Build\n"
        "3: Build & Run\n"
        "Input: "
    )

    match userInput:
        case "0": pass

        case "1":
            shell.clear()
            build()

        case "2":
            shell.clear()
            run()

        case "3":
            shell.clear()
            build()
            run()

        case _:
            shell.clear()
            print("Invalid Argument!\n")
            main()

    return

if __name__ == '__main__': main()