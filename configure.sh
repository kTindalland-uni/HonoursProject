#!/bin/sh

rm compile_commands.json
cmake -S . -B build/
cp build/compile_commands.json compile_commands.json
