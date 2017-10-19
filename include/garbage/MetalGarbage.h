#ifndef RECYCLING_METALGARBAGE_H
#define RECYCLING_METALGARBAGE_H

#include "Garbage.h"

class MetalGarbage : public Garbage {
public:
    explicit MetalGarbage(const std::string& name);
};

#endif //RECYCLING_METALGARBAGE_H
