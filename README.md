# Software design patterns in C++

## build

1. Generating
    * Windows: `cmake -G"MinGW Makefiles" -S . -B build`
    * Unix: `cmake -G"Unix Makefiles" -S . -B build`
1. Building
    * single pattern: `cmake --build build/{pattern_name}`
    * all patterns at once: `cmake --build build`

## run

`./build/{pattern_name}/{pattern_name}.exe` (use git-bash for color output)

## clang-format

`./smart-clang-format.sh` (use git-bash)
