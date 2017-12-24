#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

struct node {
    int64_t value;
    node * next;
};

class my_list {
public:
    node * begin = new node;
    my_list(vector<int64_t> numbers) {
        begin->value = numbers[0];
        node * second_x = new node;
        second_x->value = numbers[1];
        begin->next = second_x;
        for (int i = 1; i < numbers.size() - 1; ++i) {
            node * x = new node;
            x->value = numbers[i + 1];
            second_x->next = x;
            second_x = x;
        }
    }
};

void merge(int64_t left, int64_t middle, int64_t right, node * l, node * mi) {
    int64_t n1 = middle - left + 1;
    int64_t n2 = right - middle;
    vector<int64_t> L;
    vector<int64_t> R;
    L.resize(n1 + 1);
    R.resize(n2 + 1);
    node * k = l;
    for (int64_t i = 0; i < n1; ++i) {
        L[i] = l->value;
        l = l->next;
    }
    mi = mi->next;
    for (int j = 0; j < n2; ++j) {
        R[j] = mi->value;
        mi = mi->next;
    }
    L[n1] = 1e18 + 1;
    R[n2] = 1e18 + 1;
    int64_t i = 0, j = 0;
    for (int64_t m = left; m <= right; ++m) {
        if (L[i] <= R[j]) {
            k->value = L[i];
            i += 1;
        } else {
            k->value = R[j];
            j += 1;
        }
        k = k->next;
    }
}

void merge_sort(int left, int right, node * l) {
    if (left < right) {
        int middle = (left + right) / 2;
        node * m = l;
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
    cin >> N;
    vector<int64_t> numbers;
    numbers.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> numbers[i];
    }
    my_list list_numbers(numbers);
    node * x = new node;
    x = list_numbers.begin;
    merge_sort(0, N - 1, x);
    for (int i = 0; i < N; ++i) {
        cout << x->value << ' ';
        x = x->next;
    }
}