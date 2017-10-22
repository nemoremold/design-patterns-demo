#ifndef _SERVICE_LINE_HPP_
#define _SERVICE_LINE_HPP_

#include <queue>
#include <memory>
#include <string>

class ServiceLine {
public:
    std::shared_ptr<ServiceLine> clone() {
        return std::shared_ptr<ServiceLine>(new ServiceLine(*this));
    }

    std::string serve() {
        std::string s = _names.front();
        _names.pop();
        return s;
    }

    void add(std::string s) {
        _names.push(s);
    }

private:
    std::queue<std::string> _names;
};

#endif
