#!/bin/bash

find src -name *.[ch]pp | xargs clang-format -style=Chromium -i
