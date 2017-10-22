#ifndef _TOOLBOX_HPP_
#define _TOOLBOX_HPP_

#include "utility/vector.hpp"

#include <memory>
#include <iostream>

// "Interface": lowest common denominator
class Tool {
public:
    virtual void exert() = 0;
};

// Scalar class and "is-a" relationship
class Spanner : public Tool {
    void exert() {
        std::cout << "Exerting spanner..." << std::endl;
    }
};

class Screwdriver : public Tool {
    void exert() {
        std::cout << "Exerting screwdriver..." << std::endl;
    }
};

class Pincher : public Tool {
    void exert() {
        std::cout << "Exerting pincher..." << std::endl;
    }
};

// Vector class and "is-a" relationship
class Toolbox : public Tool {
    // "Container" coupled to the interface
    dp::vector<std::shared_ptr<Tool>> children;

public:
    void add(std::shared_ptr<Tool> tool) {
        children.push_back(tool);
    }

    void exert() {
        std::cout << "Container toolbox:" << std::endl;
        for (auto it = children.begin(); it != children.end(); ++it) {
            // Use polymorphism to delegate to children
            (*it)->exert();
        }
    }
};

#endif
