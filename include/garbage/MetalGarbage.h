#ifndef RECYCLING_METALGARBAGE_H
#define RECYCLING_METALGARBAGE_H

#include "Garbage.h"

class MetalGarbage : public Garbage {
public:
    explicit MetalGarbage(const std::string& name);
    static const size_t weight = 10;
};

#endif //RECYCLING_METALGARBAGE_H
