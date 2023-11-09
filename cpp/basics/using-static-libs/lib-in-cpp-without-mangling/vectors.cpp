#include <iostream>
#include <vector>
#include "vectors.h"


class Class01 {
public:
    Class01(int size, int defaultValue)
        // fill the vector with defaultValue
        : mArray(size, defaultValue) {}
    ~Class01() {}
    int getItem(int index) {
        // at(index) does the same
        return mArray[index];
    }
private:
    std::vector<int> mArray;
};


void
display_vector_initialization (int defaultValue)
{
    Class01 class01{10, defaultValue};
    std::cout <<
      "[$] Example of initialization in class using constructor initialization list => " <<
      class01.getItem(2) <<
      std::endl;
}

// Functions are accessible from outside even if 
// no public declaration is specified in the include file.
// Here in C++ it's possible to use `extern "C"` on function definitions
// to disable name mangling.
extern "C"
void _hidden_in_cpp() {
    std::cout << "[$] Ey! I'm a not publicly declared in the include file of this C++ lib." << std::endl;
}
