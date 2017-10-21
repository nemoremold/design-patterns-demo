#ifndef _SHARED_PTR_HPP_
#define _SHARED_PTR_HPP_

#include <cstddef>
#include <functional>

namespace {

template <typename T>
class shared_ptr {

public:
    using deleter_t = std::function<void (T *)>;

    // default ctor
    explicit shared_ptr(T *t, deleter_t d = [](T *t){ delete t; }) : t(t), count(new size_t(1)), deleter(d) { }

    // copy ctor
    shared_ptr(const shared_ptr &sp) : count(sp.count), t(sp.t), deleter(sp.deleter) {
        ++(*count);
    }

    // move ctor
    shared_ptr(const shared_ptr &&sp) : count(sp.count), t(sp.t), deleter(std::move(sp.deleter)) { }

    // dtor
    inline ~shared_ptr(void) {
        deconstructor();
    }

    inline shared_ptr &operator=(shared_ptr &sp) {
        ++(*sp.count);
        deconstructor();
        count = sp.count;
        t = sp.t;
        deleter = sp.deleter;
        return *this;
    }

    T& operator*() const { return *t; }

    T* operator->() const { return t; }

    void reset() {
        deconstructor();
    }

    void reset(T *p) {
        if (t) {
            deconstructor();
            t = p;
            count = new std::size_t(1);
        }
    }

    void reset(T *p, deleter_t d) {
        reset(p);
        deleter = d;
    }

private:
    std::size_t *count;
    T *t;
    deleter_t deleter;

    inline void deconstructor() {
        if (t) {
            --(*count);
            if (*count == 0) {
                deleter(t);
                delete count;
            }
        }
        t = nullptr;
        count = nullptr;
    }
};

}

#endif
