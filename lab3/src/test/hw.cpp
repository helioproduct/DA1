#include <iostream>

int main() {
    int *a = (int *)malloc(100 * sizeof(int));
    a[100] = 100;
    a[0] = 1;

    std::cout << a[0];

    return 0;
}