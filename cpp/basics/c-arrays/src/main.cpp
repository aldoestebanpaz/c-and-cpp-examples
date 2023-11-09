#include <iostream>
#include <string>

// Example of array initialization using constructor initialization list.
class Class01 {
public:
    Class01()
        : mArray { 0, 11, 22, 33, 44, 55, 66, 77, 88, 99 } {}
    ~Class01() {}
    int getItem(int index) {
        return mArray[index];
    }
private:
    int mArray[10];
};


// Example of array initialization using inline initialization of non-static member.
class Class02 {
public:
    Class02() {}
    ~Class02() {}
    int getItem(int index) {
        return mArray[index];
    }
private:
    int mArray[10] { 0, 111, 222, 333, 444, 555, 666, 777, 888, 999 };
};


// Example of array initialization for a static member.
class Class03 {
public:
    Class03() {}
    ~Class03() {}
    int getItem(int index) {
        return mArray[index];
    }
private:
    static int mArray[10];
};

int Class03::mArray[] { 123, 456, 789, 444, 555, 666, 777, 888, 999 };


// Example of array size in templated class.
// NOTE: This is a bad use of templates.
template<int ARRAY_LEN>
class Class04 {
public:
    Class04() {}
    ~Class04() {}
    int getItem(int index) {
        return mArray[index];
    }
private:
    static int mArray[ARRAY_LEN];
};


// Example using dynamic allocation.
//
// NOTE: Unless needed for efficiency reasons, this is not recommended. Try to use std:vector instead.
//
// NOTE:
// You will need dynamic allocation when the size comes from dynamic information (runtime)
// because it is not possible to create a statically sized array as before when the size
// is unknown on compile time.
// 
// If you do dynamic allocation of arrays you will also need...
// - a destructor,
// - a copy constructor,
// - and an assignment operator
//
// Using a std::vector gives you exactly the same functionality and abstracts these problems.
class Class05 {
public:
    Class05(int size)
        : mArray(new int[size]) {}
    ~Class05() {}
    int getItem(int index) {
        return mArray[index];
    }
private:
    static int *mArray;
};

int main() {

    int array01[10] { 12, 45, 78, 44, 55, 66, 77, 88, 99 };
    std::cout <<
      "[+] Example of array initialization using inline initialization => " <<
      array01[2] <<
      std::endl;


    int array02[10];
    array02[2] = 99;
    std::cout <<
      "[+] Example of default array initialization and assigning a new value separately => " <<
      array02[2] <<
      std::endl;


    Class01 class01;
    std::cout <<
      "[+] Example of array initialization in class using constructor initialization list => " <<
      class01.getItem(2) <<
      std::endl;
    

    Class02 class02;
    std::cout <<
      "[+] Example of array initialization in class using inline initialization of non-static member => " <<
      class02.getItem(2) <<
      std::endl;

    
    Class03 class03;
    std::cout <<
      "[+] Example of array initialization in class for a static member => " <<
      class03.getItem(2) <<
      std::endl;


    // NOTE: This is a bad use of templates
    Class04<10> class04;
    std::cout <<
      "[+] [not-recommended] Example of array size in templated class => " <<
      class04.getItem(2) <<
      std::endl;


    return 0;
}
