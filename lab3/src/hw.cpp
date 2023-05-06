#include <iostream>

int main() {

//    std::cout << "Hello world" << std::endl;

    int *a = (int*) malloc(100 * sizeof(int));
    a[100] = 100;
    a[0] = 1;

    std::cout << a[0];

    return 0;
}