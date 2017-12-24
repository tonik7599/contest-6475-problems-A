#include <iostream>

struct MyList {
    int value;
    MyList * p;

    MyList()
            : p(nullptr)
    { }

    MyList(int a)
            : value(a)
            , p(nullptr)
    { }
};

MyList* merge(MyList* first, int n) {
    if(n == 1)
        return first;

    MyList* second = first;
    int length1 = n / 2;
    int length2 = n - n / 2;
    for (int i = 0; i != length1 - 1; ++i) {
        second = second->p;
    }
    MyList* term = second;
    second = second->p;
    term->p = nullptr;
    first = merge(first, length1);
    second = merge(second, length2);
    MyList* num;
    MyList* last;
    if (first->value <= second->value) {
        num = first;
        last = num;
        first = first->p;
    } else {
        num = second;
        last = num;
        second = second->p;
    }

    while (first != nullptr && second != nullptr) {
        if (first->value <= second->value) {
            last->p = first;
            last = first;
            first = first->p;
        } else {
            last->p = second;
            last = second;
            second = second->p;
        }
    }
    if (first == nullptr)
        last->p = second;
    if (second == nullptr)
        last->p = first;

    return num;
}

int main() {
    int n;
    std::cin >> n;
    MyList* last = new MyList;
    MyList* begin = last;
    for (int i = 0; i != n; ++i) {
        int a;
        std::cin >> a;
        last->value = a;
        if (i != n - 1) {
            last->p = new MyList;
            last = last->p;
        } else {
            last->p = nullptr;
        }
    }
    last = merge(begin, n);

    MyList* iter = last;
    while (iter != nullptr) {
        std::cout << iter->value << ' ';
        iter = iter->p;
    }
}