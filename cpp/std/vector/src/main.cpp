#include <iostream>
#include <string>
#include <vector>


// Example of static initialization.
void basic_vector01() {
    std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    std::cout << "Size: " << vec.size() << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    std::cout << "Max_Size: " << vec.max_size() << std::endl;

    std::cout << "The vector elements are: ";
    for (std::vector<int>::iterator i = vec.begin(); i != vec.end(); ++i)
        std::cout << *i << " ";
    std::cout << std::endl;
}


// Example of dynamic initialization.
// NOTE:
// manual dynamic allocation is not required
// because the template class std::vector manages it internally. 
void basic_vector02(int size) {
    std::vector<int> vec(size);
    // fill the vector with 10
    vec.assign(vec.size(), 10);

    std::cout << "Size: " << vec.size() << std::endl;

    std::string values_s;

    // loop using iterators
    // NOTE: begin() and end() are the non-const alternatives of cbegin() and cend()
    for (auto i = vec.cbegin(); i != vec.cend(); ++i)
        values_s.append(std::to_string(*i) + ", ");
    // print
    values_s.erase(values_s.cend() - 2, values_s.cend());
    std::cout << "The vector elements are: " << values_s << std::endl;
    values_s.clear();

    // loop using subscript operator (operator[]) (aka. array subscript operator)
    for (int i = 0; i < vec.size(); i++)
        // at(i) does the same
        values_s.append(std::to_string(vec[i]) + ", ");
    // print
    values_s.erase(values_s.cend() - 2, values_s.cend());
    std::cout << "The vector elements are: " << values_s << std::endl;
}


// Example of zero initialization with multiple dynamic allocations.
//
// NOTE:
//
// Vectors are re-sizeable. size() tells you how many elements you currently have.
// capacity() tells you how large the size can get before the vector needs to
// reallocate memory for itself.
//
// Size: the number of items currently in the vector.
//
// Capacity: is the amount of space that the vector is currently using. That is,
//   it says how many items can be fit in the array under the hood before it is "full".
//   Once full, adding new items will result in a new, larger block of memory being allocated
//   and the existing items being copied to it.
void basic_vector03() {
    std::vector<int> vec;

    std::cout << "---------- 0 items" << std::endl;

    std::cout << "Size: " << vec.size() << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    std::cout << "Max_Size: " << vec.max_size() << std::endl;

    std::cout << "---------- adding 1 item" << std::endl;

    vec.push_back(123);
    std::cout << "Size: " << vec.size() << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    std::cout << "Max_Size: " << vec.max_size() << std::endl;

    std::cout << "---------- adding 1 item" << std::endl;

    vec.push_back(456);
    std::cout << "Size: " << vec.size() << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    std::cout << "Max_Size: " << vec.max_size() << std::endl;

    std::cout << "---------- adding 1 item" << std::endl;

    vec.push_back(789);
    std::cout << "Size: " << vec.size() << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    std::cout << "Max_Size: " << vec.max_size() << std::endl;

    std::cout << "---------- adding 2 items" << std::endl;

    vec.push_back(987);
    vec.push_back(654);
    std::cout << "Size: " << vec.size() << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    std::cout << "Max_Size: " << vec.max_size() << std::endl;

    std::cout << "---------- shrinking" << std::endl;

    vec.shrink_to_fit();
    std::cout << "Size: " << vec.size() << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    std::cout << "Max_Size: " << vec.max_size() << std::endl;
}


// Example of std::vector as a class member
// NOTE: std:vector uses dynamic allocation and implements RAII internally.
class Class01 {
public:
    Class01(int size)
        // fill the vector with 123
        : mArray(size, 123) {}
    ~Class01() {}
    int getItem(int index) {
        // at(index) does the same
        return mArray[index];
    }
private:
    std::vector<int> mArray;
};


int main() {

    // Example of static initialization.
    std::cout << "[+] Example of static initialization" << std::endl;
    basic_vector01();


    // Example of dynamic initialization.
    std::cout << "[+] Example of dynamic initialization" << std::endl;
    int size;
    size = 22; // suppose this value is calculated on runtime
    basic_vector02(size);


    // Example of zero initialization with multiple dynamic allocations.
    std::cout << "[+] Example of zero initialization with multiple dynamic allocations" << std::endl;
    basic_vector03();


    Class01 class01{10};
    std::cout <<
      "[+] Example of initialization in class using constructor initialization list => " <<
      class01.getItem(2) <<
      std::endl;

    return 0;
}
