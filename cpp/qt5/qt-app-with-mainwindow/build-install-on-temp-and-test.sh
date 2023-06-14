rm -rf build && mkdir build

# generate
cmake \
  -DCMAKE_BUILD_TYPE=debug \
  -DCMAKE_INSTALL_PREFIX=/tmp/sample-app-testing \
  -S . \
  -B build

# build
make -C build VERBOSE=1

# install for debug
make -C build install

# list everything in installation dir
tree /tmp/sample-app-testing

# run from install dir
/tmp/sample-app-testing/bin/sample-app --version
# /tmp/sample-app-testing/bin/sample-app
LANG=es.UTF-8 /tmp/sample-app-testing/bin/sample-app

# uninstall
rm -rf ~/.config/qt-samples
xargs rm < build/install_manifest.txt
