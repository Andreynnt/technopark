#include <iostream>


void square(int *array, int n) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        res = res + i + i + 1;
        array[i] = res;
    }
}

int main() {
    int n = 0;
    std::cin >> n;
    auto *array = new int[n];
    square(array, n);
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    square(array, n);
    delete[] array;
    return 0;
}
