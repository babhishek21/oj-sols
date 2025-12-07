# oj-sols
Solutions to problems in Online Judges
===
This repository was made with the intention of backing up my solutions for future reference, as well as serve as a reference for people who might be looking for help. Please use this sparingly. **The code is not maintained, and probably never will be.**

The repository does not reflect the actual statistics of my sessions on online judges. There are a few problems whose solutions I forgot to save, or cannot otherwise source. I'll try to keep it complete.

But _no guarantees_. I am too lazy.

Oh! And do take a look at the [LICENSE file](LICENSE) before you do something with the code.

## Config & Setup

- I prefer using vanilla Sublime Text 4.
- Use the [oj-sols.sublime-project](oj-sols.sublime-project) file to open this repo as a project.

### Toolchain
1. **[🅲＋＋]**  If using Clang (ideally on macOS), copy my patched [snippets/stdc++.h](snippets/stdc++.h) header file to `/usr/local/include/bits/` (or any other `CPLUS_INCLUDE_PATH` location, in the `bits` subdiretory).

> [!IMPORTANT]
> Update the path to the header in the `HEADER_SRC` variable in the [Makefile](Makefile#L6). 

> [!TIP]
> No need to worry about G++ as <bits/stdc++.h> is included pre-compiled by default.

2. **[🅲＋＋]** Get [cxx-prettyprint](https://louisdx.github.io/cxx-prettyprint/) and place the header files in to `/usr/local/include/custom/` (or any other `CPLUS_INCLUDE_PATH` location, in the `custom` subdiretory). Useful for pretty-printing most STL containers.

3. **[🅲＋＋]** Copy `snippets/*.sublime-snippet` to the Sublime Text User Packages folder (`~/Library/Application Support/Sublime Text/Packages` in macOS).

4. **[🅲＋＋]** **[☕️]** Makefile and `mymake`
    1. Copy [mymake.fish](mymake.fish) to `~/.config/fish/functions/` (or wherever your custom fish shell functions live).
        - `mymake` is a custom fish shell function to auto-detect the Makefile at root directory of this repo and pass it to `make` correctly, regardless of the working subdirectory.
    2. [Makefile](Makefile) targets macOS and Unix-like platforms.
        - Run `mymake thing.bin` to smart-compile `thing.cpp` or `thing.java` into `thing.bin`
        - Run `mymake cpp.thing.bin` to force compile `thing.cpp` into `thing.bin` (bonafide executable)
        - Run `mymake java.thing.bin` to force compile `thing.java` into `thing.bin` (bash script that runs the generated Java class file)
        - Run `mymake clean` to clean out executable and generated files
        - Where Clang is available, `make` will try to precompile the <bits/stdc++.h> header for use.
