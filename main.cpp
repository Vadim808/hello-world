#include <iostream>
#include <vector>
#include <cstdint>

template <typename T>
struct node {
    T value;
    node * next;
};

class my_list {
public:
    node<int64_t> * begin = new node<int64_t>;
    my_list(std::vector<int64_t> numbers) {
        begin->value = numbers[0];
        node<int64_t> * second_x = new node<int64_t>;
        second_x->value = numbers[1];
        begin->next = second_x;
        for (int i = 1; i < numbers.size() - 1; ++i) {
            node<int64_t> * x = new node<int64_t>;
            x->value = numbers[i + 1];
            second_x->next = x;
            second_x = x;
        }
    }
};

void merge(int64_t left, int64_t middle, int64_t right, node<int64_t> * l, node<int64_t> * mi) {
    int64_t n1 = middle - left + 1;
    int64_t n2 = right - middle;
    node<int64_t> * L = new node<int64_t>;
    node<int64_t> * R = new node<int64_t>;
    node<int64_t> * startL = L;
    node<int64_t> * startR = R;
    node<int64_t> * k = l;
    for (int64_t i = 0; i < n1; ++i) {
        L->value = l->value;
        l = l->next;
        L->next = new node<int64_t>;
        L = L->next;
    }
    L->value = 1e18 + 1;
    mi = mi->next;
    for (int j = 0; j < n2; ++j) {
        R->value = mi->value;
        mi = mi->next;
        R->next = new node<int64_t>;
        R = R->next;
    }
    R->value = 1e18 + 1;
    for (int64_t m = left; m <= right; ++m) {
        if (startL->value <= startR->value) {
            k->value = startL->value;
            startL = startL->next;
        } else {
            k->value = startR->value;
            startR = startR->next;
        }
        k = k->next;
    }
}

void merge_sort(int left, int right, node<int64_t> * l) {
    if (left < right) {
        int middle = (left + right) / 2;
        node<int64_t> * m = l;
        for (int64_t i = left; i < middle; ++i) {
            m = m->next;
        }
        merge_sort(left, middle, l);
        merge_sort(middle + 1, right, m->next);
        merge(left, middle, right, l, m);
    }
}

int main() {
    int N;
    std::cin >> N;
    std::vector<int64_t> numbers;
    numbers.resize(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> numbers[i];
    }
    my_list list_numbers(numbers);
    node<int64_t> * x = new node<int64_t>;
    x = list_numbers.begin;
    merge_sort(0, N - 1, x);
    for (int i = 0; i < N; ++i) {
        std::cout << x->value << ' ';
        x = x->next;
    }
}
