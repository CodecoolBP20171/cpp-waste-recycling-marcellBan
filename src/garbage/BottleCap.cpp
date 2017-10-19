#include "../../include/garbage/BottleCap.h"

BottleCap::BottleCap(const std::string& color) : color(color) {}

const std::string& BottleCap::getColor() const {
    return color;
}
