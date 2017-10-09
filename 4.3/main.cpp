#include <iostream>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;

#define START_SIZE 3
#define PUSH_COMMAND 3
#define POP_COMMAND 2

template <class T>
class Stack {
public:
    Stack();
    ~Stack();

    Stack(const Stack<T>& stack) = delete;
    Stack(Stack<T>&& other) { *this = std::forward<Stack>(other); }

    Stack<T>& operator=(const Stack<T>& other) = delete;
    Stack<T>& operator=(Stack<T>&& other);

    void Push(const T& value);
    int Pop();
    void getInfo();
    int getSize() { return size; }
    T getLastElem();
    int getRealSize() { return realSize; }
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
Stack<T>& Stack<T>::operator=(Stack<T>&& other)
{
    delete[] buffer;
    buffer = other.buffer;
    other.buffer = nullptr;
    return *this;
}

template <class T>
Stack<T>::~Stack()
{
    delete[] buffer;
}


template <class T>
void Stack<T>::getInfo()
{
    cout << "real size = " << realSize << " size = " << size << endl;
    cout << "buffer: ";
    for (int i = 0; i < realSize; i++) {
        cout << buffer[i] << " ";
    }
    cout << endl << endl;
}

template <class T>
T Stack<T>::getLastElem() {
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
        T *tmp = new T[size];
        for (int i = 0; i < realSize; i++) {
            tmp[i] = buffer[i];
        }
        tmp[realSize++] = value;
        delete[] buffer;
        buffer = tmp;
    }
}

template <class T>
int Stack<T>::Pop()
{
    if (!realSize)
        return -1;
    buffer[realSize - 1] = 0;
    realSize--;
    return 0;
}



class Queue {
public:
    Queue() = default;
    ~Queue() = default;

    Queue(const Queue& other) = delete;
    Queue(Queue&& other) = delete;

    Queue& operator=(const Queue& other) = delete;
    Queue& operator=(Queue&& other) = delete;

    void push(int value);
    int pop(int value);
    void showQueue();
private:
    Stack<int> stack1;
    Stack<int> stack2;

};

void Queue::push(int value) {
    stack1.Push(value);
}

int Queue::pop(int value) {
    if (stack2.getRealSize()) {
        if (stack2.Pop() == -1) {
            return -1;
        }
    } else {
        if (!stack1.getRealSize())
            return -1;
        int size = stack1.getRealSize() - 1;
        for (int i = 0; i < size; i++) {
            int tmp = stack1.getLastElem();
            stack2.Push(tmp);
            stack1.Pop();
        }
        int tmp = stack1.getLastElem();
        if (tmp == value) {
            stack1.Pop();
            return 0;
        }
        return -1;
    }
    return 0;
}

void Queue::showQueue() {
    stack1.getInfo();
    stack2.getInfo();
}

int main () {
    Queue q;
    std::string result = "YES";
    int commandsAmount = 0, command = 0, value = 0;
    cin >> commandsAmount;
    for (int i = 0; i < commandsAmount; i++) {
        cin >> command;
        cin >> value;
        if (command == POP_COMMAND) {
            if (q.pop(value) == -1 && value != -1) {
                result = "NO";
                cout << result;
                return 0;
            }
        } else if (command == PUSH_COMMAND) {
            q.push(value);
        }
    }
    //q.showQueue();
    cout << result;
}

