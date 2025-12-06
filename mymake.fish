function mymake --wraps make --description "Run make from the git repo root"
    # 1. Find the root of the git repository
    # We use 'command git' to avoid aliases, and capture stderr to null
    set -l repo_root (command git rev-parse --show-toplevel 2>/dev/null)

    # 2. Check if we are inside a repo
    if test -z "$repo_root"
        echo "Error: Not inside a Git repository."
        return 1
    end

    # 3. Run make
    # -f: Point to the Makefile at the repo root
    # -C: Tell make to execute 'as if' it were in the current directory ($PWD)
    # $argv: Pass all arguments (e.g., 'ProblemA', 'clean', 'java.ProblemB')
    make -f "$repo_root/Makefile" -C "$PWD" CP_MODE=1 $argv
end
