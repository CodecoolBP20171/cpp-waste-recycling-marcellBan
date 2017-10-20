#ifndef RECYCLING_BOTTLECAP_H
#define RECYCLING_BOTTLECAP_H

#include <string>

class BottleCap {
public:
    explicit BottleCap(const std::string& color);
    const std::string& getColor() const;
    static const size_t weight = 1;
private:
    std::string color;
};

#endif //RECYCLING_BOTTLECAP_H
