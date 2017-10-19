#ifndef RECYCLING_DUSTBIN9K_H
#define RECYCLING_DUSTBIN9K_H

#include "Dustbin.h"
#include "../garbage/MetalGarbage.h"
#include "../garbage/BottleCap.h"

class Dustbin9k : public Dustbin {
public:
    explicit Dustbin9k(const std::string& color);
    void throwOutMetalGarbage(std::unique_ptr<MetalGarbage>& metalGarbage);
    void throwOutBottleCap(std::unique_ptr<BottleCap>& bottleCap);
    void emptyContents() override;
    bool isEmpty() const override;
    size_t getMetalCount() const;
    size_t getBottlecapCount() const;
    size_t getCurrentMetalCapacity() const;
    size_t getCurrentBottlecapCapacity() const;
protected:
    size_t metalIndex, bottlecapIndex;
    size_t currentMetalCapacity, currentBottlecapCapacity;
    std::unique_ptr<std::unique_ptr<MetalGarbage>[]> metalContent;
    std::unique_ptr<std::unique_ptr<BottleCap>[]> bottlecapContent;
};

#endif //RECYCLING_DUSTBIN9K_H
