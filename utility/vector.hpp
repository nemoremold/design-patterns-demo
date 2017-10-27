#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <cstddef>

namespace dp {

template <typename TV>
class vector {
private:
    size_t _size, _capacity;
    TV *data;

public:
    class iterator {
    private:
        vector *vec;
        ptrdiff_t _index;

    public:
        friend class vector;
        iterator(vector *vec, size_t _index) : vec(vec), _index(_index) { }

        TV &operator*() const {
            return vec->data[_index];
        }

        TV *operator->() const {
            return &(vec->data[_index]);
        }

        iterator &operator++() {
            ++_index;
            return *this;
        }

        iterator operator++(int) {
            iterator iter(*this);
            ++_index;
            return iter;
        }

        iterator &operator--() {
            --_index;
            return *this;
        }

        iterator operator--(int) {
            iterator iter(*this);
            --_index;
            return iter;
        }

        iterator next() const {
            return iterator(vec, _index + 1);
        }

        iterator prev() const {
            return iterator(vec, _index - 1);
        }

        bool operator==(const iterator &other) const {
            return vec == other.vec && _index == other._index;
        }

        bool operator!=(const iterator &other) const {
            return !(*this == other);
        }

        ptrdiff_t index() const {
            return _index;
        }
    };

    vector(size_t capacity = 8) : _size(0), _capacity(0), data(NULL) {
        ensure_capacity(capacity);
    }

    vector(const vector &vec) : _size(vec._size), _capacity(vec._capacity), data(new TV[vec._capacity]) {
        for (size_t i = 0; i < _size; ++i) {
            data[i] = vec.data[i];
        }
    }

    vector &operator=(const vector &vec) {
        if (data) {
            delete[] data;
        }
        _size = vec._size;
        _capacity = vec._capacity;
        data = new TV[vec._capacity];
        for (size_t i = 0; i < _size; ++i) {
            data[i] = vec.data[i];
        }
        return *this;
    }

    template <typename CALLABLE>
    void for_each(CALLABLE &func) {
        for (iterator iter = begin(); iter != end(); ++iter) {
            func(*iter);
        }
    }

    iterator begin() {
        return iterator(this, 0);
    }

    iterator iter_at(ptrdiff_t i) {
        return iterator(this, i);
    }

    iterator end() {
        return iterator(this, _size);
    }

    size_t size() const {
        return _size;
    }

    size_t capacity() const {
        return _capacity;
    }

    TV &operator[](size_t index) {
        return data[index];
    }

    const TV &operator[](size_t index) const {
        return data[index];
    }

    size_t push_back(const TV &v) {
        ensure_capacity(_size + 1);
        data[_size] = v;
        return ++_size;
    }

    TV pop_back() {
        --_size;
        return data[_size];
    }

    void remove(ptrdiff_t s, ptrdiff_t t) {
        for (ptrdiff_t i = t; i < (ptrdiff_t)_size; ++i, ++s) {
            data[s] = data[i];
        }
        _size = s;
    }

    void remove(const iterator &s, const iterator &t) {
        remove(s._index, t._index);
    }

    void remove(const iterator &iter) {
        remove(iter._index, iter._index + 1);
    }

    void insert(ptrdiff_t at, const TV &v) {
        ensure_capacity(_size + 1);
        for (ptrdiff_t i = _size - 1; i >= at; --i) {
            data[i + 1] = data[i];
        }
        data[at] = v;
        ++_size;
    }

    void insert(const iterator &iter, const TV &v) {
        insert(iter._index, v);
    }

    template <typename TITERATOR>
    void copy(const iterator &iter, TITERATOR iter_begin, size_t n) {
        ensure_capacity(_size + n);
        for (ptrdiff_t i = _size - 1; i >= iter._index; --i) {
            data[i + n] = data[i];
        }

        for (size_t i = 0; i < n; ++i, ++iter_begin) {
            data[i + iter._index] = *iter_begin;
        }
        _size += n;
    }

    ~vector() {
        if (data) {
            delete[] data;
        }
    }

private:
    void ensure_capacity(size_t required_capacity) {
        if (_capacity >= required_capacity) {
            return;
        }

        if (_capacity == 0) {
            _capacity = required_capacity;
        }
        else {
            while (_capacity < required_capacity)  {
                // Table doubling
                _capacity <<= 1;
            }
        }
        TV *new_data = new TV[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
    }
};

}

#endif
