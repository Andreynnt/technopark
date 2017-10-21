/*
 * В город N приехал цирк с командой атлетов. Они хотят удивить горожан города N — выстроить из
 * своих тел башню максимальной высоты. Башня — это цепочка атлетов, первый стоит на земле,
 * второй стоит у него на плечах, третий стоит на плечах у второго и т.д. Каждый атлет
 * характеризуется силой si (kg) и массой mi (kg). Сила — это максимальная масса, которую
 * атлет способен держать у себя на плечах. К сожалению ни один из атлетов не умеет программировать,
 * так как всю жизнь они занимались физической подготовкой, и у них не было времени на изучение
 * языков программирования. Помогите им, напишите программу, которая определит максимальную высоту башни,
 * которую они могут составить. Известно, что если атлет тяжелее, то он и сильнее: если mi>mj, то si > sj.
 * Атлеты равной массы могут иметь различную силу
 *
 */

#include <iostream>
#include <cassert>

#define START_SIZE 50

using std::cin;
using std::cout;
using std::endl;

template <class T>
class Array {
private:
    T *buffer = nullptr;
    int size = 0;
    int realSize = 0;
public:
    Array();
    ~Array();
    void Push(const T& value);
    T& operator[](int index) const;
    int GetRealSize() const { return realSize; }
};

template <class T>
Array<T>::Array() :
        size(START_SIZE)
{
    buffer = new T[START_SIZE];
}

template <class T>
Array<T>::~Array() {
    delete[] buffer;
}

template <class T>
T& Array<T>::operator[](int index) const{
    assert (index >= 0);
    return buffer[index];
}

template <class T>
void Array<T>::Push(const T &value) {
    if (realSize < size) {
        buffer[realSize++] = value;
    } else {
        size *= 2;
        auto *tmp = new T[size];
        for (int i = 0; i < realSize; i++) {
            tmp[i] = buffer[i];
        }
        tmp[realSize++] = value;
        delete[] buffer;
        buffer = tmp;
    }
}



class sportsMan {
private:
    int Weight = 0;
    int Strength = 0;
public:
    sportsMan() = default;
    sportsMan(int weight, int strength);
    int GetWeight() const { return  Weight; }
    int GetStrength() const { return Strength; }
};

sportsMan::sportsMan(int weight, int strength) :
        Weight(weight), Strength(strength)
{

}



void quickSort(const Array<sportsMan>& array, int left, int right) {
    int l_hold = left, r_hold = right;
    sportsMan tmp = array[left];
    int pivot = tmp.GetStrength();

    while (left < right) {
        while ((array[right].GetStrength() >= pivot) && (left < right))
            right--;
        if (left != right) {
            array[left] = array[right]; // перемещаем элемент [right] на место разрешающего
            left++;
        }
        while ((array[left].GetStrength() <= pivot) && (left < right))
            left++;
        if (left != right) {
            array[right] = array[left];
            right--;
        }
    }

    array[left] = tmp; // ставим разрешающий элемент на место
    pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot) //Рекурсивно вызываем сортировку для левой и правой части массива
        quickSort(array, left, pivot - 1);
    if (right > pivot)
        quickSort(array, pivot + 1, right);
}

int maxSize(const Array<sportsMan>& array, int size) {
    int res = 0, maxWeight = 0;
    for (int i = 0; i < size; i++) {
        if (array[i].GetStrength() >= maxWeight) {
            res++;
            maxWeight += array[i].GetWeight();
        }
    }
    return res;
}



int main(int argc, char* argv[]) {
    int weight = 0, strength = 0;
    Array<sportsMan> array;
    while (cin >> weight) {
        cin >> strength;
        sportsMan s(weight, strength);
        array.Push(s);
    }

    quickSort(array, 0, array.GetRealSize() - 1);

    cout << maxSize(array, array.GetRealSize());
}