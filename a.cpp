#include <iostream>
#include <vector>

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
MyList<T>* merge(MyList<T>* first) {
    if (first->next == nullptr)
        return first;

    MyList<T> *second = first;
    MyList<T> *cursor = first;
    MyList<T> *term = second;
    while (cursor->next != nullptr) {
        term = second;
        second = second->next;
        cursor = cursor->next;
        if (cursor->next != nullptr) {
            cursor = cursor->next;
        }
    }
    term->next = nullptr;
    return split(merge(first), merge(second));
}

template<typename T>
MyList<T>* split(MyList<T>* first, MyList<T>* second) {
    MyList<T>* num = nullptr;
    MyList<T>* last = nullptr;

    while (first || second) {
        MyList<T>* cur = nullptr;
        if (!second || (first && first->value < second->value)) {
            cur = first;
            first = first->next;
        } else {
            cur = second;
            second = second->next;
        }
        if (last) {
            last->next = cur;
        } else {
            num = cur;
        }
        last = cur;
    }

    return num;
}

template<typename T>
MyList<T>* mergesort(MyList<T>* num) {
    return merge(num);
}

int main() {
    int n;
    std::cin >> n;
    MyList<int>* last = nullptr;
    MyList<int>* begin = nullptr;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        if (i == 0) {
            last = new MyList<int> (a);
            begin = last;
        } else {
            last->next = new MyList<int>(a);
            last = last->next;
        }
    }
    last = mergesort(begin);

    MyList<int>* iter = last;
    while (iter != nullptr) {
        std::cout << iter->value << ' ';
        iter = iter->next;
    }
    return 0;
}
