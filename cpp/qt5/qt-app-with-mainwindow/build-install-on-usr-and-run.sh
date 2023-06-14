# Run with sudo:
#   sudo ${PWD}/build-install-on-usr-and-run.sh

rm -rf build && mkdir build

# generate
cmake \
  -DCMAKE_INSTALL_PREFIX=/usr \
  -S . \
  -B build

# build
make -C build VERBOSE=1

# install
make -C build install

# list installed files
cat build/install_manifest.txt

# run
sample-app --version
# sample-app
LANG=es_ES.UTF-8 sample-app

# uninstall
rm -rf ~/.config/qt-samples
xargs rm < build/install_manifest.txt
