#!/usr/bin/env bash

CURRENT_SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

#************************************************
# Current script location
#************************************************

cd ${CURRENT_SCRIPT_DIR}

rm -rf tmp && mkdir tmp


#************************************************
# Sample App
#************************************************

rm -rf build && mkdir build

# generate
cmake \
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
${CURRENT_SCRIPT_DIR}/tmp/bin/dbus-service


#************************************************
# Uninstall everything
#************************************************

# xargs rm < build/install_manifest.txt
# rm -rf build

# rm -rf tmp
