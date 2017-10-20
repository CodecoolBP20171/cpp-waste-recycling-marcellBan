#ifndef RECYCLING_PLASTICGARBAGE_H
#define RECYCLING_PLASTICGARBAGE_H

#include "Garbage.h"

class PlasticGarbage : public Garbage {
public:
    explicit PlasticGarbage(const std::string& name);
    void clean();
    bool IsClean() const;
    static const size_t weight = 3;
private:
    bool isClean;
};

#endif //RECYCLING_PLASTICGARBAGE_H
