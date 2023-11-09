#include <iostream>


// Option 1: The include file already has a `extern "C"` wrapper
#include "lib-in-c/messages.h"
// Option 2: Use this if the include file does not contains the `extern "C"` wrapper
// extern "C" {
// #include "lib-in-c/messages.h"
// }


// Option 1: ...
// #include "lib-in-cpp-without-mangling/vectors.h"
// Option 3: If you know the interface and no include is available,
// then you can put the declarations here
extern "C" {

void display_vector_initialization (int defaultValue);

}


#include "lib-in-cpp-with-mangling/vectors2.h"


// Hidden functions on C and C++ lib without name mangling
// Option 3 is a trick that allows access to libraries without using include files
extern "C" {

// function defined in messages.c
void _hidden_in_c (void);
// function defined in vectors.cpp
void _hidden_in_cpp (void);

}


// Hidden functions on C++ lib with name mangling
// function defined in vectors2.cpp
void _hidden_in_cpp_with_mangling ();


void hello_from_c_lib() {
    // Using a designated initializer [(ANSI) C99]
    char message[] = "Hello World!";
    MessagesRecord msg = { .message = message };

    // Another usage
    //char message[] = "Hello World!";
    //MessagesRecord msg = { message };

    // Printing null
    core_print(NULL, MESSAGES_MODE_CONCISE);

    // Printing in concise mode
    core_print(&msg, MESSAGES_MODE_CONCISE);

    // Printing in verbose mode
    core_print(&msg, MESSAGES_MODE_VERBOSE);
}


void hello_from_hidden_functions() {
    // Option 3 is a trick that allows access to libraries without using include files
    _hidden_in_c();
    _hidden_in_cpp();
    _hidden_in_cpp_with_mangling();
}


void hello_from_cpp_lib_without_mangling() {
    display_vector_initialization(777);
}


void hello_from_cpp_lib_with_mangling() {
    Class01 class01{10};
    std::cout <<
      "[&] Example of initialization in class using constructor initialization list => " <<
      class01.getItem(2) <<
      std::endl;
}


int main() {
    std::cout << "[+] Hello from app." << std::endl;

    hello_from_c_lib();

    hello_from_cpp_lib_without_mangling();

    hello_from_cpp_lib_with_mangling();

    hello_from_hidden_functions();

    return 0;
}
