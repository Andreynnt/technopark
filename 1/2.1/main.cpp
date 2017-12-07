/*
 * Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1].
 * Необходимо найти первую пару индексов i0 и j0, i0 ≤ j0, такую что A[i0] + B[j0] = max {A[i] + B[j],
 * где 0 <= i < n, 0 <= j < n, i <= j}. Время работы - O(n).
 * n ≤ 100000.
 *
 */

#include <iostream>
#include <vector>
#include <cassert>

typedef std::vector<int> intVector;
using std::cin;
using std::cout;

//ввод вектора
void readVector(intVector &array, const int len) {
    int tmp = 0;
    for (int i = 0; i < len; i++) {
        cin >> tmp;
        array.push_back(tmp);
    }
}

//вывод вектора
void printVector(const intVector& array) {
    for (auto i : array) {
        cout << i << " ";
    }
}

//нахождение первых индексов максимальных элементов
std::vector<int> maxSum(intVector &result, const intVector &firstArray, const intVector &secondArray, const int n) {
    int maxIndexFirst = 0, maxIndexSecond = 0, tmpIndex = 0;
    for (int i = 1; i < n; i++) {
        if (firstArray[i] > firstArray[tmpIndex]) {
            tmpIndex = i;
        }

        if (firstArray[tmpIndex] + secondArray[i] > firstArray[maxIndexFirst] + secondArray[maxIndexSecond]) {
            maxIndexSecond = i;
            maxIndexFirst = tmpIndex;
        }
    }
    result.push_back(maxIndexFirst);
    result.push_back(maxIndexSecond);
    return result;
}

int main() {
    int len = 0;
    cin >> len;
    assert(len <= 100000);
    intVector firstArray, secondArray, result;
    readVector(firstArray, len);
    readVector(secondArray, len);
    maxSum(result, firstArray, secondArray, len);
    printVector(result);
    return 0;
}
