# Software design patterns in C++

## Generate

### Unix

`cmake -G"Unix Makefiles" -DCMAKE_CXX_COMPILER=clang++ -S . -B build`

### Windows (assume you have VS building suite)

`cmake -S . -B build`

## Build

### Single pattern

#### Windows

`cmake --build build --target {pattern_name}`

#### Unix

`cmake --build build/{pattern_name}`

### All patterns

`cmake --build build`

## Run

### Unix

`./build/bin/{pattern_name}`

### Windows

`.\build\bin\{BuildType}\{pattern_name}.exe`

## Utils

### Format all .hpp and .cpp files in project (Unix-only)

`./smart-clang-format.sh`
