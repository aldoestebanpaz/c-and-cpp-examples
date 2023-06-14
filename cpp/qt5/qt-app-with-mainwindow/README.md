# Simple application using QMainWindow

## How to build and run

```sh
mkdir build && cd build

# generate
rm -rf *
cmake \
  -DCMAKE_BUILD_TYPE=debug \
  -DCMAKE_INSTALL_PREFIX=/usr \
  ..

# build
make

# run
${PWD}/sample-app
```

## How to build and install for testing

```sh
mkdir build && cd build

# generate
rm -rf *
cmake \
  -DCMAKE_BUILD_TYPE=debug \
  -DCMAKE_INSTALL_PREFIX=/tmp/sample-app-testing \
  ..

# build
make

# install in a temp dir
make install

# run
/tmp/sample-app-testing/bin/sample-app

# uninstall
xargs rm < install_manifest.txt
```

## How to build and deploy in /usr/local

WARNING: This process does not offers a to uninstall the files installed (at least you maintain a copy of build/install_manifest.txt). It is better to build, install in a temp directory and package the files to be able to uninstall them later.

```sh
mkdir build && cd build

# generate
rm -rf *
cmake \
  -DCMAKE_BUILD_TYPE=debug \
  -DCMAKE_INSTALL_PREFIX=/usr/local \
  ..

# build
make

# install in a temp dir
make install

# run
sample-app
```

## How to build and install for later packaging

```sh
mkdir build && cd build

# generate
rm -rf *
cmake \
  -DCMAKE_BUILD_TYPE=debug \
  -DCMAKE_INSTALL_PREFIX=/usr \
  ..

# build
make

# install in a temp dir
make \
  DESTDIR=${PWD}/install \
  install

# package everyting located in ${PWD}/install
```

## How to debug

```sh
# move to build dir
# mkdir build && cd build

# build
# cmake ... -DCMAKE_BUILD_TYPE=debug ...
# make

# debug
# with GDB -- format `gdb --args a.out 1 2 3`
gdb ${PWD}/sample-app
# with LLDB (from LLVM) -- format `lldb -- a.out 1 2 3`
lldb ${PWD}/sample-app
```

### Example commands with GDB

More info in [GDB to LLDB command map](https://lldb.llvm.org/use/map.html).

**Before launch**

- `(gdb) set args 1 2 3` and `(gdb) run` launch a process with arguments 1 2 3 without having to supply the args every time.
- `(gdb) set env DEBUG 1` or `(gdb) unset env DEBUG` set or unset environment variables for process before launching.

**Launch**

- `(gdb) run <args>` or `(gdb) r <args>` launch.

**Execution**

- `(gdb) next` or `(gdb) n` step over.
- `(gdb) step` or `(gdb) s` step into.
- `(gdb) continue` or `(gdb) c` continue, keep running.
- `(gdb) finish` step out (Step out of the currently selected frame).

**Information**

NOTE: here I'm using most common register $pc or $rip nowadays, replace with $eip or very rarely $ip if needed.

- `(gdb) info sources` show source files.
- `(gdb) info functions` show all defined functions files.
- `(gdb) show args` show the arguments that will be or were passed to the program when run.
- `(gdb) frame` or `(gdb) f` show the current frame and source line.
- `(gdb) info line *$pc` or `(gdb) info line *$rip` show line number and file source.
- `(gdb) list *$pc` or `(gdb) list *$rip` prints out the surrounding lines with the current line in the center.
- `(gdb) backtrace` or `(gdb) bt` or `(gdb) where` (same effect) prints out the call stack (aka. backtrace), ending on the current line.
- `(gdb) display argc` and`(gdb) display argv` display the variables "argc" and "argv" every time you stop.
- `(gdb) info args` and `(gdb) info locals` show the arguments and local variables for the current frame.
- `(gdb) p bar` show the contents of local or global variable "bar".
- `(gdb) p/x bar` show the contents of local variable "bar" formatted as hex.
- `(gdb) p *ptr@10` print an array of integers in memory, assuming we have a pointer like "int *ptr".

**Executable and Shared Library Query Commands**

- `(gdb) info function <FUNC_REGEX>` look up functions matching a regular expression in a binary and shared libraries.
- `(gdb) info shared` list the main executable and all dependent shared libraries.

**Breakpoints**

- `(gdb) break main` set a breakpoint at all functions named main.
- `(gdb) break test.c:12` set a breakpoint in file test.c at line 12.
- `(gdb) info break` list all breakpoints.
- `(gdb) delete 1` delete a breakpoint.
- `(gdb) disable 1` or `(gdb) enable 1` disable or enable a breakpoint.
