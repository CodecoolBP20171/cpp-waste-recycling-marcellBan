#ifndef RECYCLING_PAPERGARBAGE_H
#define RECYCLING_PAPERGARBAGE_H

#include "Garbage.h"

class PaperGarbage : public Garbage {
public:
    explicit PaperGarbage(const std::string& name);
    void squeeze();
    bool IsSqueezed() const;
private:
    bool isSqueezed;
};

#endif //RECYCLING_PAPERGARBAGE_H
