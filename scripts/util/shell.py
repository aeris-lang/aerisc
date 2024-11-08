import subprocess
import os

def cmd(cmd:str) -> str:
    try:
        result = subprocess.run(cmd, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        return result.stdout.decode().strip()

    except subprocess.CalledProcessError as e:
        return e.stderr.decode().strip()

def clear() -> None:
    os.system("clear")
    return