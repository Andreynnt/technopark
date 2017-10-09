#include <iostream>

struct Nod {
    int A = 1;
    int B = 1;
}typedef Nod;

int getNod1(int a, int b) {
    if (b == 0)
        return a;
    return getNod1(b, a % b);
}

int getNod(int i, int j) {
    while (i != j) {
        if (i > j) {
            i -= j;
        } else {
            j -= i;
        }
    }
    return i;
}

void makeNode(Nod& nod, int n) {
    int r = 0, b = 0, result = 0;
    for (int a = 1; a <= n / 2; a++) {
        b = n - a;
        r = getNod1(a, b);
        //std::cout << "a = " << a << " b = " << b << std::endl;
        if (r > result) {
            result = r;
            nod.A = a;
            nod.B = b;
        }
    }
}


int main() {
    int n = 0;
    std::cin >> n;
    Nod nod;
    makeNode(nod, n);
    std::cout << nod.A << " " << nod.B;
    return 0;
}