#!/usr/bin/env bash

CURRENT_SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

#************************************************
# Current script location
#************************************************

cd ${CURRENT_SCRIPT_DIR}

rm -rf tmp && mkdir tmp


#************************************************
# Shared module
#************************************************

cd shared-module

rm -rf build && mkdir build

# generate
cmake \
  -DCMAKE_BUILD_TYPE=debug \
  -DCMAKE_INSTALL_PREFIX=${CURRENT_SCRIPT_DIR}/tmp \
  -S . \
  -B build

# build
make -C build

# install for debug
make -C build install

cd ..


#************************************************
# Shared library
#************************************************

cd libsample

rm -rf build && mkdir build

# generate
cmake \
  -DCMAKE_MODULE_PATH=${CURRENT_SCRIPT_DIR}/tmp/share/cmake \
  -DCMAKE_BUILD_TYPE=debug \
  -DCMAKE_INSTALL_PREFIX=${CURRENT_SCRIPT_DIR}/tmp \
  -S . \
  -B build

# build
make -C build

# install for debug
make -C build install

cd ..


#************************************************
# Sample Client
#************************************************

cd sample-client

rm -rf build && mkdir build

# generate
cmake \
  -DCMAKE_MODULE_PATH=${CURRENT_SCRIPT_DIR}/tmp/share/cmake \
  -DCMAKE_BUILD_TYPE=debug \
  -DCMAKE_INSTALL_PREFIX=${CURRENT_SCRIPT_DIR}/tmp \
  -S . \
  -B build

# build
make -C build VERBOSE=1

# install for debug
make -C build install

cd ..


#************************************************
# Run
#************************************************

QT_LOGGING_RULES='*.debug=true;qt.*=false' \
LANG=es.UTF-8 \
LD_LIBRARY_PATH=${CURRENT_SCRIPT_DIR}/tmp/lib:$LD_LIBRARY_PATH \
${CURRENT_SCRIPT_DIR}/tmp/bin/sampleclient


#************************************************
# Uninstall everything
#************************************************

cd ${CURRENT_SCRIPT_DIR}/shared-module
xargs rm < build/install_manifest.txt
rm -rf build

cd ${CURRENT_SCRIPT_DIR}/libsample
xargs rm < build/install_manifest.txt
rm -rf build

cd ${CURRENT_SCRIPT_DIR}/sample-client
xargs rm < build/install_manifest.txt
rm -rf build

cd ${CURRENT_SCRIPT_DIR}
rm -rf tmp
