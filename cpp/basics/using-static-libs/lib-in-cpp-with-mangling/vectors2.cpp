#include <iostream>
#include "vectors2.h"

Class01::Class01(int size)
        // fill the vector with defaultValue
        : mArray(size, 555) {}

Class01::~Class01() {}

int Class01::getItem(int index) {
    // at(index) does the same
    return mArray[index];
}

// Functions are accessible from outside even if 
// no public declaration is specified in the include file.
void _hidden_in_cpp_with_mangling () {
    std::cout << "[&] Ey! I'm a not publicly declared in the include file of this C++ lib with mangling." << std::endl;
}
