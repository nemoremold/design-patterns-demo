#ifndef _LIST_HPP_
#define _LIST_HPP_

template <class T>
struct list_node {
  list_node<T> *_prev;
  list_node<T> *_next;
  T _data;
  list_node(const T &data = T()) : _prev(nullptr), _next(nullptr), _data(data) {}
};

template <class T, class Ref, class Ptr>
struct list_iterator {
  typedef list_iterator<T, Ref, Ptr> Self;
  list_node<T> *_node;

  list_iterator() {}

  list_iterator(list_node<T> *node) : _node(node) {}
 
  Ref operator*() const {
    return _node->_data;
  }

  Ptr operator->() const {
    return &(operator*());
  }

  bool operator==(const Self &x) {
    return (_node == x._node);
  }

  bool operator!=(const Self &x) {
    return (_node != x._node);
  }

  Self &operator++() {
    _node = _node->_next;
    return *this;
  }
  
  Self operator++(int) {
    Self old = *this;
    ++(*this);
    return old;
  }
  
  Self &operator--() {
    (_node = _node->_prev);
    return *this;
  }
  
  Self operator--(int) {
    Self old = *this;
    --(*this);
    return old;
  }
};

template <class T>
class list {
public:
  typedef list_iterator<T, T&, T*> Iterator;
  typedef list_iterator<T, const T&, const T*> ConstIterator;

private:
  typedef T &Reference;

public:
  list() : _list(new list_node<T>()) {
    _list->_next = _list;
    _list->_prev = _list;
  }
  
  Iterator Begin() {
    return Iterator(_list->_next);
  }
  
  Iterator End() {
    return Iterator(_list);
  }
  
  ConstIterator Begin() const {
    return _list->_next;
  }
  
  ConstIterator End() const {
    return _list->_next;
  }
  
  void PushBack(const T &data) {
    Insert(End(), data);
  }
  
  void PopBack() {
    Erase(Iterator(_list->_prev));
  }
  
  void PushFront(const T &data) {
    Insert(Iterator(_list->_next), data);
  }
  
  void PopFront() {
    Erase(Iterator(_list->_next));
  }
  
  Reference Front() {
    return *Begin();
  }
  
  Reference Back() {
    return *(--End());
  }

  void Insert(Iterator pos, const T &data) {
    list_node<T> * cur = pos._node;
    list_node<T> * prev = cur->_prev;
    list_node<T> * tmp = new list_node<T>(data);
    tmp->_next = cur;
    cur->_prev = tmp;
    prev->_next = tmp;
    tmp->_prev = prev;
  }
  
  Iterator &Erase(Iterator pos) {
    list_node<T> * cur = pos._node;
    list_node<T> * prev = cur->_prev;
    list_node<T> * next = cur->_next;
    prev->_next = next;
    next->_prev = prev;
    delete cur;
    return Iterator(next);
  }
  
  bool Empty() const {
    if (_list->_next == _list) {
      return true;
    }
    else {
      return false;
    }
  }
  
  size_t Size() {
    int size = 0;
    list_node<T> * start = _list->_next;
    list_node<T> * end = _list;
    while (start != end) {
      ++size;
      start = start->_next;
    }
    return size;
  }

protected:
  list_node<T> *_list;
};

#endif
