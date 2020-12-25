# Software design patterns in C++

## Generate

### Unix

`cmake -G"Unix Makefiles" -DCMAKE_CXX_COMPILER=clang++ -S . -B build`

### Windows

`cmake -G"MinGW Makefiles" -S . -B build`

## Build

### Single pattern

`cmake --build build/{pattern_name}`

### All patterns

`cmake --build build`

## Run

### Unix

`./build/{pattern_name}/{pattern_name}`

### Windows

`./build/{pattern_name}/{pattern_name}.exe` (use git-bash for color output)

## Utils

### Format all .hpp and .cpp files in project

`./smart-clang-format.sh`
