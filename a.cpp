#include <iostream>

template<typename T>
struct MyList {
    T value;
    MyList<T> * next;

    MyList<T>()
            : next(nullptr)
    { }

    MyList<T>(T a)
            : value(a)
            , next(nullptr)
    { }

    ~MyList<T>() {
        delete *this;
    }
};

template<typename T>
MyList<T>* merge(MyList<T>* first, int n) {
    if(n == 1)
        return first;

    MyList<T>* second = first;
    for (int i = 0; i != n / 2 - 1; ++i) {
        second = second->next;
    }
    MyList<T>* term = second;
    second = second->next;
    term->next = nullptr;
    first = merge(first, n / 2);
    second = merge(second, n - n / 2);
    MyList<T>* num = nullptr;
    MyList<T>* last = nullptr;

    while (first != nullptr || second != nullptr) {
        if (!second || (first && first->value < second->value)) {
            if (last) {
                last->next = first;
            } else {
                num = first;
            }
            last = first;
            first = first->next;
        } else {
            if (last) {
                last->next = second;
            } else {
                num = second;
            }
            last = second;
            second = second->next;
        }
    }

    return num;
}

int main() {
    int n;
    std::cin >> n;
    MyList<int>* last = new MyList<int>;
    MyList<int>* begin = last;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        last->value = a;
        if (i != n - 1) {
            last->next = new MyList<int>;
            last = last->next;
        } else {
            last->next = nullptr;
        }
    }
    last = merge(begin, n);

    MyList<int>* iter = last;
    while (iter != nullptr) {
        std::cout << iter->value << ' ';
        iter = iter->next;
    }
    return 0;
}
