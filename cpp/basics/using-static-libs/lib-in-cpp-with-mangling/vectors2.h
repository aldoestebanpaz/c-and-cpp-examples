#ifndef VECTORS2_H
#define VECTORS2_H

#include <vector>

class Class01 {
public:
    Class01(int size);
    ~Class01();
    int getItem(int index);
private:
    std::vector<int> mArray;
};

#endif /* VECTORS2_H */
