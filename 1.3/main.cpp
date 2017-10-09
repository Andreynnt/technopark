#include <iostream>

int nod(int i, int j) {
    while (i != j) {
        if (i > j) {
            i -= j;
        } else {
            j -= i;
        }
    }
    return i;
}

int main() {
    int upLeft, downLeft, upRight, downRight;
    std::cin >> upLeft;
    std::cin >> downLeft;
    std::cin >> upRight;
    std::cin >> downRight;

    int down = downLeft * downRight;
    int up = upRight * downLeft + upLeft * downRight;

    int n = 0;
    while (n != 1) {
        n = nod(up, down);
        up /= n;
        down /= n;
    }
    std::cout << up << " " << down;
    return 0;
}
