#!/bin/bash

find . -path ./build -prune -false -o -name *.[ch]pp | xargs clang-format -style=file -i
