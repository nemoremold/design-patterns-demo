#ifndef _LIST_HPP_
#define _LIST_HPP_

#include <cstddef>

namespace np {

template <class T>
struct list_node {
  list_node<T> *_prev;
  list_node<T> *_next;
  T _data;
  list_node(){}
  list_node(const T &data) : _prev(nullptr), _next(nullptr), _data(data) {}
};

template <class T, class Ref, class Ptr>
struct list_iterator {
  typedef list_iterator<T, Ref, Ptr> self;
  list_node<T> *_node;

  list_iterator() {}

  list_iterator(list_node<T> *node) : _node(node) {}
 
  Ref operator*() const {
    return _node->_data;
  }

  Ptr operator->() const {
    return &(operator*());
  }

  bool operator==(const self &x) {
    return (_node == x._node);
  }

  bool operator!=(const self &x) {
    return (_node != x._node);
  }

  self &operator++() {
    _node = _node->_next;
    return *this;
  }
  
  self operator++(int) {
    self old = *this;
    ++(*this);
    return old;
  }
  
  self &operator--() {
    (_node = _node->_prev);
    return *this;
  }
  
  self operator--(int) {
    self old = *this;
    --(*this);
    return old;
  }
};

template <class T>
class list {
public:
  typedef list_iterator<T, T&, T*> iterator;
  typedef list_iterator<T, const T&, const T*> const_iterator;

private:
  typedef T &reference;

public:
  list() : _list(new list_node<T>()) {
    _list->_next = _list;
    _list->_prev = _list;
  }

  ~list(){
    iterator it = begin();
    while(it != end()){
      it = erase(it);
    }
    erase(it);
  }
  
  iterator begin() {
    return iterator(_list->_next);
  }
  
  iterator end() {
    return iterator(_list);
  }
  
  const_iterator begin() const {
    return _list->_next;
  }
  
  const_iterator end() const {
    return _list;
  }
  
  void push_back(const T &data) {
    insert(end(), data);
  }
  
  void pop_back() {
    erase(iterator(_list->_prev));
  }
  
  void push_front(const T &data) {
    insert(iterator(_list->_next), data);
  }
  
  void pop_front() {
    erase(iterator(_list->_next));
  }
  
  reference front() {
    return *begin();
  }
  
  reference back() {
    return *(--end());
  }

  void insert(iterator pos, const T &data) {
    list_node<T> *cur = pos._node;
    list_node<T> *prev = cur->_prev;
    list_node<T> *tmp = new list_node<T>(data);
    tmp->_next = cur;
    cur->_prev = tmp;
    prev->_next = tmp;
    tmp->_prev = prev;
  }
  
  iterator erase(iterator pos) {
    list_node<T> *cur = pos._node;
    list_node<T> *prev = cur->_prev;
    list_node<T> *next = cur->_next;
    prev->_next = next;
    next->_prev = prev;
    delete cur;
    return iterator(next);
  }
  
  bool empty() const {
    return _list->_next == _list;
  }
  
  size_t size() {
    int size = 0;
    list_node<T> *start = _list->_next;
    list_node<T> *end = _list;
    while (start != end) {
      ++size;
      start = start->_next;
    }
    return size;
  }

protected:
  list_node<T> *_list;
};

}

#endif
