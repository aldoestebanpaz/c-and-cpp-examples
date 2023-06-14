#include <iostream>
#include <pthread.h>

int main() {

    std::cout << "[+] pthread_t: " << pthread_self() << "\n";

    return 0;
}
