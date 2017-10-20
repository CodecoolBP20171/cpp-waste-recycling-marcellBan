#ifndef RECYCLING_GARBAGE_H
#define RECYCLING_GARBAGE_H

#include <string>

class Garbage {
public:
    explicit Garbage(const std::string& name);
    const std::string& getName() const;
    static const size_t weight = 5;
private:
    std::string name;
};

#endif //RECYCLING_GARBAGE_H
