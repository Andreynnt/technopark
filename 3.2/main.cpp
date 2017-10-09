#include <iostream>
#include <vector>
#include <cassert>

using std::cin;
using std::cout;

class Array{
public:
    Array() = default;
    explicit Array(int length);
    Array(Array&& other);
    Array(Array &other) = delete;
    Array& operator=(Array&& other);
    ~Array() { delete[] buffer; };

    int getSize() { return size; };
    const int& operator[](int index) const;
    int& operator[](int index);

private:
    int *buffer = nullptr;
    int size = 0;
};

Array::Array(const int length) {
    buffer = new int[length];
    size = length;
}

Array::Array(Array&& other) :
        buffer (other.buffer),
        size (other.size)
{
    other.buffer = nullptr;
};

Array& Array::operator=(Array&& other) {
    buffer = other.buffer;
    size = other.size;
    other.buffer = nullptr;
    return *this;
}

const int& Array::operator[](int index) const {
    assert(0 <= index && index <= size);
    return buffer[index];
}

int& Array::operator[](int index) {
    const Array& constThis = *this;
    return const_cast<int&>(constThis[index]);
}

void readArray(Array& array, const int len) {
    int tmp = 0;
    for (int i = 0; i < len; i++) {
        cin >> tmp;
        array[i] = tmp;
    }
}

void printArray(Array &array) {
    for (int i = 0; i < array.getSize(); i++) {
        cout << array[i] << " ";
    }
}

struct IndexInterval {
    int first = 0;
    int last = 0;
};


int searchBend(Array& array, struct IndexInterval& interval) {
    if (!array.getSize()) {
        return 0;
    }
    if (array.getSize() == 1) {
        interval.first = 0;
        interval.last = 0;
        return 1;
    }

    int low = 0, high = 1;
    while (high < array.getSize() - 1 && array[high - 1] < array[high]) {
        low = high;
        high *= 2;
    }

    if (high > array.getSize() - 1) {
        high = array.getSize() - 1;
    }
    interval.first = low;
    interval.last = high;
//    cout << "low = " << low << " high = " << high << std::endl;
//    cout << "interval size = " << high - low + 1 << std::endl;
    return high - low + 1;

}


int* makeArray(Array &array, struct IndexInterval& interval, int intervalSize) {
    int *span = new int[intervalSize];
    for (int i = 0, j = interval.first; i < intervalSize; i++, j++) {
        span[i] = array[j];
    }

    return span;
}

int binary(int *a, int size, struct IndexInterval& interval) {
    int left = 0, mid = 0;
    int right = size - 1;

    if (size == 2) {
        return a[0] > a[1] ? interval.first : interval.last;
    }

    while (left < right) {
        mid = left + (right - left) / 2;
        if (a[mid] > a[mid - 1] && a[mid] > a[mid + 1]) {
//            std::cout << "in interval it is " <<  mid << std::endl;
            return mid + interval.first;
        }
        if (a[mid] > a[mid - 1]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
//    std::cout << "in interval it is " <<  mid << std::endl;
    return left + interval.first;
}

int main() {
    int length = 0;
    cin >> length;
    Array array(length);
    readArray(array, length);
    struct IndexInterval interval;
    int intervalSize = searchBend(array, interval);

    int  *span = makeArray(array, interval, intervalSize);

//    cout << "interval : ";
//    for (int i = 0; i < intervalSize; i++) {
//        cout << span[i] << " ";
//    }
//    cout << std::endl;

    int res = binary(span, intervalSize, interval);
    cout << res;

    delete[] span;
    return 0;
}
