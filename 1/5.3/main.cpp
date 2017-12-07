/*
 * Дана последовательность N прямоугольников различной ширины и высоты (wi,hi). Прямоугольники расположены,
 * начиная с точки (0, 0), на оси ОХ вплотную друг за другом (вправо).Требуется найти
 * M - площадь максимального прямоугольника (параллельного осям координат),
 * который можно вырезать из этой фигуры.
*/

#include <iostream>
#include <cassert>
#include <memory>

#define START_SIZE 10

using std::cin;
using std::cout;
using std::endl;

template <class T>
class Stack {
public:
    Stack();
    explicit Stack(int size);
    ~Stack();

    Stack(const Stack<T>& stack) = delete;
    Stack(Stack<T>&& other) noexcept { *this = std::forward<Stack>(other); }
    Stack<T>& operator=(const Stack<T>& other) = delete;
    Stack<T>& operator=(Stack<T>&& other);
    T& operator[](int index) const;

    void Push(const T& value);
    T Pop();
    void GetInfo() const;
    int GetSize() const { return size; }
    T& GetLastElem() const;
    int GetRealSize() const { return realSize; }
private:
    T *buffer = nullptr;
    int size = 0;
    int realSize = 0;
};

template <class T>
Stack<T>::Stack() :
    size(START_SIZE)
{
    buffer = new T[START_SIZE];
}

template <class T>
T& Stack<T>::operator[](int index) const
{
    assert(0 <= index && index < size);
    return buffer[index];
}

template <class T>
Stack<T>::Stack(int Size) :
    size(Size), realSize(0)
{
    buffer = new T[Size];
}

template <class T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other)
{
    delete[] buffer;
    buffer = other.buffer;
    realSize = other.realSize;
    size = other.size;
    other.buffer = nullptr;
    return *this;
}

template <class T>
Stack<T>::~Stack()
{
    delete[] buffer;
}

template <class T>
void Stack<T>::GetInfo() const
{
    cout << "real size = " << realSize << endl << " size = " << size << endl;
    cout << "buffer: " << endl;
    for (int i = 0; i < realSize; i++) {
        cout << "\t" << buffer[i];
    }
    cout << endl << endl;
}

template <class T>
T& Stack<T>::GetLastElem() const
{
    assert(realSize > 0);
    return buffer[realSize - 1];
}

template  <class T>
void Stack<T>::Push(const T &value)
{
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

template <class T>
T Stack<T>::Pop()
{
    T tmp = buffer[realSize - 1];
    realSize--;
    return tmp;
}



class Rectangle {
public:
    Rectangle() = default;
    Rectangle(const Rectangle& other);
    Rectangle(int Width, int Height);
    Rectangle& operator=(const Rectangle& other);
    ~Rectangle() = default;
    void SetSize(int Width, int Height);
    void PlusWidth(int Width) { width += Width; };
    int GetWidth() { return  width; }
    int GetHeight() { return height; }
    int GetArea() { return  width * height; }
    friend std::ostream& operator<<(std::ostream&, const Rectangle&);
private:
    int width = 0;
    int height = 0;
};


Rectangle::Rectangle(int Width, int Height)
{
    width = Width;
    height = Height;
}

Rectangle::Rectangle(const Rectangle &other) :
    width(other.width), height(other.height)
{
}

void Rectangle::SetSize(int Width, int Height)
{
    width = Width;
    height = Height;
}

Rectangle& Rectangle::operator=(const Rectangle& other) {
    width = other.width;
    height = other.height;
}

std::ostream& operator<<(std::ostream& out, const Rectangle& rectangle)
{
    out << "width = " << rectangle.width << " height = " << rectangle.height << endl;
}



void joinRecatangles(Stack<Rectangle>& stack, Rectangle *previous, Rectangle *current, int& maxHeight) {
    stack.GetLastElem().PlusWidth(previous->GetWidth());

    int beforeMaxHeight =  stack.GetLastElem().GetHeight();

    //сравниваем высоты прямоугольника, стоявшего перед максимальным с текущим
    if (beforeMaxHeight > current->GetHeight()) {
        maxHeight = beforeMaxHeight;
    } else if (beforeMaxHeight == current->GetHeight()){
        stack.GetLastElem().PlusWidth(current->GetWidth());
        maxHeight = current->GetHeight();
    } else {
        //прямоугольник перед найденным ниже текущего
        maxHeight = current->GetHeight();
        Rectangle r(previous->GetWidth() + current->GetWidth(), maxHeight);
        stack.Push(r);
    }
}

int countMaxArea(Rectangle *RectanglesArray, int size) {
    assert(size > 0);
    Stack<Rectangle> stack;
    stack.Push(RectanglesArray[0]);
    int maxArea = RectanglesArray[0].GetArea();

    for (int i = 1; i < size; i++) {
        Rectangle *previous = &stack.GetLastElem(), *current = &RectanglesArray[i];
        //ищем первый максимальный прямоугольник
        if (current->GetHeight() >= previous->GetHeight()) {
            stack.Push(*current);
            //cout << "New rect in stack: width = " << current->GetWidth() << " height = " << current->GetHeight() << endl;
        } else {
            //встретили прямоугольник, который ниже
            //срезаем пока не дойдем до найденного до уровня
            int maxHeight = previous->GetHeight();

            while (maxHeight > current->GetHeight()) {
                *previous = stack.Pop();
                //cout << "previous area " << previous->GetArea() << endl;
                if (previous->GetArea() > maxArea) {
                    maxArea = previous->GetArea();
                }

                if (!stack.GetRealSize()) {
                    maxHeight = current->GetHeight();
                    Rectangle r(previous->GetWidth() + current->GetWidth(), maxHeight);
                    stack.Push(r);
                } else {
                    //cout << "Stack r s = " << stack.GetRealSize() << endl;
                    //склеиваем два прямоугольника
                    joinRecatangles(stack, previous, current, maxHeight);
                }
            }

        }
    }
    return maxArea;
}



int main() {
    int size = 0, width = 0, height = 0;
    cin >> size;
    size++;
    auto *RectanglesArray = new Rectangle[size];

    for (int i = 0; i < size - 1; i++) {
        cin >> width;
        cin >> height;
        RectanglesArray[i].SetSize(width, height);
    }

    RectanglesArray[size - 1].SetSize(0, 0);

    int answer = countMaxArea(RectanglesArray, size);
    cout << answer;
    delete[] RectanglesArray;
    return 0;
}
