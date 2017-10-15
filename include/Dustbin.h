#ifndef RECYCLING_DUSTBIN_H
#define RECYCLING_DUSTBIN_H

#include <bits/unique_ptr.h>

#include "Garbage.h"
#include "PaperGarbage.h"
#include "PlasticGarbage.h"

class Dustbin {
public:
    static const size_t INITIAL_CAPACITY = 10;
    static const size_t CAPACITY_STEP = 5;
    explicit Dustbin(const std::string& color);
    void throwOutGarbage(std::unique_ptr<Garbage>& garbage);
    void throwOutPaperGrabage(std::unique_ptr<PaperGarbage>& paperGarbage);
    void throwOutPlasticGarbage(std::unique_ptr<PlasticGarbage>& plasticGarbage);
    void emptyContents();
private:
    std::string color;
    size_t garbageIndex, paperIndex, plasticIndex;
    size_t garbageCurrentCapacity, paperCurrentCapacity, plasticCurrentCapacity;
    std::unique_ptr<std::unique_ptr<PaperGarbage>[]> paperContent;
    std::unique_ptr<std::unique_ptr<PlasticGarbage>[]> plasticContent;
    std::unique_ptr<std::unique_ptr<Garbage>[]> houseWasteContent;
};

#endif //RECYCLING_DUSTBIN_H
