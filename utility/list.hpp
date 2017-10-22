#ifndef _LIST_HPP_
#define _LIST_HPP_

#include <cstddef>

namespace dp {

template <typename T>
struct list_node {
    list_node<T>* prev;
    list_node<T>* next;
    T data;
};

template <typename T>
class list_iterator {
private:
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;

public:
    list_iterator() : node(nullptr) {}
    list_iterator(list_node<T> *x) : node(x) {}
    list_iterator(const list_iterator<T> &x) : node(x.node) {}

    bool operator== (const list_iterator<T> &rhs) const {
        return node == rhs.node;
    }

    bool operator!= (const list_iterator<T> &rhs) const {
        return !(operator==(rhs));
    }

    reference operator* () const {
        return node->data;
    }

    pointer operator-> () const {
        return &(operator*());
    }

    list_iterator& operator++ () {
        node = node->next;
        return *this;
    }

    list_iterator operator++ (int) {
        list_iterator<T> old = *this;
        ++(*this);
        return old;
    }

    list_iterator& operator-- () {
        node = node->prev;
        return *this;
    }

    list_iterator operator-- (int) {
        list_iterator<T> old = *this;
        --(*this);
        return old;
    }

    list_node<T> *node;
};

template <typename T>
class list {
private:
    list_node<T>* node;
    static std::allocator<list_node<T> > alloc;

public:
    typedef list_iterator<T> iterator;

    iterator begin() {
        return (list_iterator<T>)node->next;
    }

    iterator end() {
        return (list_iterator<T>)node;
    }

    iterator empty() {
        return node->next == node;
    }

    size_t size() {
        size_t len = 0;
        distance(begin(), end(), len);
        return len;
    }

    T& front() {
        return *begin();
    }

    T& back() {
        return *(--end());
    }

    list() {
        empty_initialize();
    }

    ~list() {
        clear();
        if (node != nullptr) {
            delete node;
        }
    }

    void push_back(const T& x) {
        insert(end(), x);
    }

    void push_front(const T&x) {
        insert(begin(), x);
    }

    iterator insert(iterator position, const T& x) {
        list_node<T>* tmp = create_node(x);
        tmp->next = position.node;
        tmp->prev = position.node->prev;
        position.node->prev->next = tmp;
        position.node->prev = tmp;
        return tmp;
    }

    iterator erase(iterator position) {
        list_node<T>* next_node = position.node->next;
        list_node<T>* prev_node = position.node->prev;
        prev_node->next = next_node;
        next_node->prev = prev_node;
        destroy_node(position.node);
        return iterator(next_node);
    }

    void pop_front() {
        erase(begin());
    }

    void pop_back() {
        iterator tmp = end();
        erase(--tmp);
    }

    void clear() {
        list_node<T>* cur = node->next;
        while (cur != node) {
            list_node<T>* tmp = cur;
            cur = (list_node<T>*)cur->next;
            destroy_node(tmp);
        }
        node->next = node;
        node->prev = node;
    }

    void remove(const T& value) {
        iterator first = begin();
        iterator last = end();
        while (first != last) {
            iterator next = first;
            ++next;
            if (*first == value) {
                erase(first);
            }
            first = next;
        }
    }

    void unique() {
        iterator first = begin();
        iterator last = end();
        if (first == last) {
            return;
        }
        iterator next = first;
        while (++next != last) {
            if (*first == *next) {
                erase(next);
            } else {
                first = next;
            }
            next = first;
        }
    }

    void splice(iterator position, list& x) {
        if (!x.empty()) {
            transfer(position, x.begin(), x.end());
        }
    }

    void splice(iterator position, list&, iterator i) {
        iterator j = i;
        ++j;
        if (position == i || position == j) {
            return;
        }
        transfer(position, i, j);
    }

    void splice(iterator position, list&, iterator first, iterator last) {
        if (first != last) {
            transfer(position, first, last);
        }
    }

protected:
    void empty_initialize() {
        node = get_node();
        node->next = node;
        node->prev = node;
    }

    list_node<T>* get_node() {
        return alloc.allocate(1);
    }

    void put_node(list_node<T>* p) {
        alloc.deallocate(p, 1);
        return;
    }

    list_node<T>* create_node(const T& x) {
        list_node<T>* p = get_node();
        alloc.construct(&p->data, x);
        return p;
    }

    void destroy_node(list_node<T>* p) {
        alloc.destroy(&(p->data));
        put_node(p);
    }
};

template <typename T>
std::allocator<list_node<T> > list<T>::alloc;

}

#endif
