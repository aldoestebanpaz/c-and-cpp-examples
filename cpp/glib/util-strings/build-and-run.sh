#!/usr/bin/env bash

clear

CURRENT_SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

#************************************************
# Current script location
#************************************************

cd ${CURRENT_SCRIPT_DIR}

rm -rf tmp && mkdir tmp


#************************************************
# Sample
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


#************************************************
# Run
#************************************************

printf "\n\n"

${CURRENT_SCRIPT_DIR}/tmp/bin/GlibUtilStringsSampleApp

printf "\n\n"

# Wait for user input to continue
# Explanation:
# -n defines the required character count to stop reading
# -s hides the user's input
# -r causes the string to be interpreted "raw" (without considering backslash escapes)
read -n 1 -s -r -p 'Press any key to continue'
printf "\n"

#************************************************
# Uninstall everything
#************************************************

xargs rm < build/install_manifest.txt

rm -rf build

rm -rf tmp
