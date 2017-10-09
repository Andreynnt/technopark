/*
 * 1_6. Дан массив целых чисел A[0..n).
 * Не используя других массивов переставить элементы массива A  в обратном порядке за O(n).
 */

#include <assert.h>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

//переворачивание элементов в векторе
void reverse(std::vector<int> &array) {
    auto tail = array.end() - 1;
    for (auto head = array.begin(); tail - head > 0; head++, tail--) {
        int tmp = *tail;
        *tail = *head;
        *head = tmp;
    }
}

//ввод вектора
void readVector(std::vector<int> &array, const int len) {
    int tmp = 0;
    for (int i = 0; i < len; i++) {
        cin >> tmp;
        array.push_back(tmp);
    }
}

//выво вектора
void printVector(const std::vector<int> &array) {
    for (auto i : array) {
        cout << i << " ";
    }
}

int main() {
    std::vector<int> array;
    int len = 0;
    cin >> len;
    assert(len <= 10000);
    readVector(array, len);
    reverse(array);
    printVector(array);
    return 0;
}
