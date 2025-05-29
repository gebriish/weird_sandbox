import os
import subprocess
import sys

DEPENDENCIES = [
    {
        "name": "glfw",
        "path": "./lib/glfw",
        "git": "https://github.com/glfw/glfw.git",
    },
]

def clone_repo(git_url, path, tag=None):
    print(f"Cloning {git_url} into {path}...")
    subprocess.run(["git", "clone", git_url, path], check=True)
    if tag:
        print(f"Checking out tag {tag}...")
        subprocess.run(["git", "checkout", "tags/" + tag], cwd=path, check=True)

def setup_dependency(dep):
    if not os.path.exists(dep["path"]):
        os.makedirs(os.path.dirname(dep["path"]), exist_ok=True)
        clone_repo(dep["git"], dep["path"], dep.get("tag"))
    else:
        print(f"{dep['name']} already exists at {dep['path']}, skipping.")

def main():
    for dep in DEPENDENCIES:
        try:
            setup_dependency(dep)
        except subprocess.CalledProcessError as e:
            print(f"Error while setting up {dep['name']}: {e}")
            sys.exit(1)

if __name__ == "__main__":
    main()