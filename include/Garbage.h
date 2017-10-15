#ifndef RECYCLING_GARBAGE_H
#define RECYCLING_GARBAGE_H

#include <string>

class Garbage {
public:
    Garbage(const std::string& name);
    const std::string& getName() const;
private:
    std::string name;
};

#endif //RECYCLING_GARBAGE_H
