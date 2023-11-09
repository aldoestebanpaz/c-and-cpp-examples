

# Glib 2 samples

## The FindGLIB.cmake module

I've copied this package configuration file from the lxqt-build-tools package. This has a more precise way to find the required paths for build process. See in the following result, it shows that other packages provides the same file too:

```sh
apt-file search --regex "GLIB.*\.cmake"
# result:
#   cmake-vala: /usr/share/VCM/GLib/FindGLIB2.cmake
#   extra-cmake-modules: /usr/share/ECM/find-modules/FindGLIB2.cmake
#   libalglib-dev: /usr/lib/x86_64-linux-gnu/cmake/ALGLIB/ALGLIBConfig.cmake
#   lxqt-build-tools: /usr/share/cmake/lxqt-build-tools/find-modules/FindGLIB.cmake
#   qt6-base-dev: /usr/lib/x86_64-linux-gnu/cmake/Qt6/3rdparty/extra-cmake-modules/find-modules/FindGLIB2.cmake
#   wireshark-dev: /usr/lib/x86_64-linux-gnu/wireshark/cmake/FindGLIB2.cmake
#   ycm-cmake-modules: /usr/share/YCM/3rdparty/FindGLIB2.cmake
```

## What package provides glib-2 dev files?

I was able to find this dev package (libglib2.0-dev) by using the following commands:

```sh
# (1) Install apt-file and update the cache
apt-get install apt-file
apt-file update


# (2) Search pkg-config file
apt-file search --regex ".*/pkgconfig/glib-2.*\.pc$"
# result:
#   libglib2.0-dev: /usr/lib/x86_64-linux-gnu/pkgconfig/glib-2.0.pc


# (3) Alternative: search lib files
apt-file search --regex ".*/libglib-2.*\.(so|a)$"
# result:
#   libglib2.0-dev: /usr/lib/x86_64-linux-gnu/libglib-2.0.a
#   libglib2.0-dev: /usr/lib/x86_64-linux-gnu/libglib-2.0.so


# (4) Alternative: search include files
apt-file search --regex ".*/glibconfig\.h$"
# result:
#   libglib2.0-dev: /usr/lib/x86_64-linux-gnu/glib-2.0/include/glibconfig.h
apt-file search --regex ".*/glib\.h$"
# result:
#   libglib2.0-dev: /usr/include/glib-2.0/glib.h
#   libhiredis-dev: /usr/include/hiredis/adapters/glib.h
#   syslog-ng-dev: /usr/include/syslog-ng/compat/glib.h
```

## What other packages and files are distributed by libglib2?

```sh
# (1) Update cache
sudo apt-get update

# (2) Search libglib2 packages
apt-cache search libglib2
# result:
#   libglib2.0-0 - GLib library of C routines
#   libglib2.0-bin - Programs for the GLib library
#   libglib2.0-data - Common files for GLib library
#   libglib2.0-dev - Development files for the GLib library
#   libglib2.0-dev-bin - Development utilities for the GLib library
#   libglib2.0-doc - Documentation files for the GLib library
#   libglib2.0-cil - CLI binding for the GLib utility library 2.12
#   libglib2.0-cil-dev - CLI binding for the GLib utility library 2.12
#   libglib2.0-tests - GLib library of C routines - installed tests

# (3) Optional: inspect package content
apt-file list libglib2.0-dev-bin
# result:
#   ...

# (4) Install
sudo apt-get install libglib2.0-dev
```
