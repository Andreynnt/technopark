/*
 * Дано N кубиков. Требуется определить каким количеством
 * способов можно выстроить из этих кубиков широкую пирамиду.
 *
 * */

#include <iostream>

class Pyramid {
private:
    int blocksAmount = 0;
    long int height = 0;
public:
    Pyramid() = default;
    explicit  Pyramid(int n) : blocksAmount(n) { };
    long int buildPyramid();
};


//dfdfdf
long int Pyramid::buildPyramid() {
    auto **array = new long int*[blocksAmount + 1];

    for (int i = 0; i <= blocksAmount; i++) {
        array[i] = new long int[blocksAmount + 1];
    }

    for (int i = 0; i <= blocksAmount; i++) {
        for (int j = 0; j <= blocksAmount; j++) {
            if (i <= 2) {
                if (j <= i) {
                    array[i][j] = 0;
                } else {
                    array[i][j] = 1;
                }
            } else {
                array[i][j] = 0;
                for (int k = 1; k <= i; k++) {
                    //идем по диагонали
                    if (k < j) {
                        array[i][j] += array[i - k][k];
                    }
                }
            }
        }
    }

    long int result = 0;
    //проходимся по главной диагонали и подсчитываем сумму
    for (int i = 0; i <= blocksAmount; i++) {
        result += array[i][blocksAmount - i];
    }

    //освобождаем память
    for (int i = 0; i <= blocksAmount; i++) {
        delete[] array[i];
    }
    delete[] array;

    height = result;
    return result;
}


int main(){
    int n = 0;
    std::cin >> n;
    Pyramid pyramid(n);
    std::cout << pyramid.buildPyramid();
    return 0;
}
