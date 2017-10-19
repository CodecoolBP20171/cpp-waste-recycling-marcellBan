#include "../../include/garbage/PlasticGarbage.h"

PlasticGarbage::PlasticGarbage(const std::string& name) : Garbage(name), isClean(false) {
}

void PlasticGarbage::clean() {
    isClean = true;
}

bool PlasticGarbage::IsClean() const {
    return isClean;
}
