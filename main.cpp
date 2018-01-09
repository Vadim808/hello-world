#include <iostream>
#include <cstdint>

template <typename T>
struct node {
    T value;
    node * next;
};

template <typename T>
class my_list {
private:
    node<T> * end = new node<T>;
    node<T> * begin = end;
    int list_len = 0;
public:
    my_list() {}
    
    my_list(node<T> * b, node<T> * e): begin(b), end(e) {}

    node<T> * begin_node() {
        return begin;
    }
    
    void move_begin() {
        begin = begin->next;
    }
    
    node<T> * end_node() {
        return end;
    }
    
    void push_back(T x) {
        if (list_len != 0) {
            end = end->next;
        }
        list_len += 1;
        end->value = x;
        end->next = new node<T>;
    }
    
    void print(int N) {
        node<T> * x = begin;
        for (int i = 0; i < N; ++i) {
            std::cout << x->value << ' ';
            x = x->next;
        }
    }
    
    void assign_end(node<T> * x) {
        end = x;
    }
};

template <typename T>
node<T> * move_node(node<T> * n, int moves) {
    for (int i = 0; i < moves; ++i) {
        n = n->next;
    }
    return n;
}

template <typename T>
void merge(node<T> * l, node<T> * m, node<T> * r) {
    my_list<T> L(l, m);
    my_list<T> R(m->next, r);
    node<T> * end = r->next;
    L.end_node()->next = nullptr;
    R.end_node()->next = nullptr;
    while (L.begin_node() != nullptr && R.begin_node() != nullptr){
        if (L.begin_node()->value > R.begin_node()->value) {
            node<T> * n = R.begin_node();
            R.move_begin();
            n->next = L.begin_node()->next;
            L.begin_node()->next = n;
            T x = L.begin_node()->value;
            L.begin_node()->value = n->value;
            n->value = x;
            if (n->next == nullptr) {
                L.assign_end(n);
            }
        }
        L.move_begin();
    }
    if (R.begin_node() == nullptr) {
        L.end_node()->next = end;
    } else {
        L.end_node()->next = R.begin_node();
        R.end_node()->next = end;
    }
}

template <typename T>
void merge_sort(int left, int right, node<T> * l, node<T> * r) {
    if (left < right) {
        int middle = (left + right) / 2;
        node<T> * m = l;
        m = move_node(m, middle - left);
        node<T> * next_m = m->next;
        merge_sort(left, middle, l, m);
        merge_sort(middle + 1, right, next_m, r);
        m = l;
        m = move_node(m, middle - left);
        r = m;
        r = move_node(r, right - middle);
        merge(l, m, r);
    }
}

int main() {
    int N;
    std::cin >> N;
    my_list<int64_t> list;
    int64_t x;
    for (int i = 0; i < N; ++i) {
        std::cin >> x;
        list.push_back(x);
    }
    merge_sort(0, N - 1, list.begin_node(), list.end_node());
    list.print(N);
}
