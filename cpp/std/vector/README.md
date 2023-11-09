
# Simple example using std::vector

`std::vector` is one example of these self-managing data structures, and is a direct replacement for an array.

When you need an array with a dynamic size, almost always the best solution in C++ is to use a vector.

`std::vector` is a template class that encapsulate a dynamic array, stored in the heap, that grows and shrinks automatically if elements are added or removed. It provides all the hooks (begin(), end(), iterators, etc) that make it work fine with the rest of the STL. It also has several useful methods that let you perform operations that on a normal array would be cumbersome, like e.g. inserting elements in the middle (it handles all the work of moving the following elements behind the scenes).

Since it stores the elements in memory allocated on the heap, it has some overhead (I mean, it is less efficient) in respect to static arrays.
