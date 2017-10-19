#include "../../include/garbage/Garbage.h"

Garbage::Garbage(const std::string& name) : name(name) {}

const std::string& Garbage::getName() const {
    return name;
}
