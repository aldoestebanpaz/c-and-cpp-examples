


## Superbuild mode

```sh
rm -rf build && mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=. ..
cd ..



rm -rf build && mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=${PWD} ..
make
cd ..
```

### What is CMAKE_PREFIX_PATH?

CMAKE_PREFIX_PATH is a semicolon-separated list of directories specifying installation prefixes to be searched by the `find_package()`, `find_program()`, `find_library()`, `find_file()`, and `find_path()` commands. Each command will add appropriate subdirectories (like `bin`, `lib`, or `include`) as specified in its own documentation.

By default this is empty.
