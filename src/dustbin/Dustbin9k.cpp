#include "../../include/dustbin/Dustbin9k.h"
#include "../../include/dustbin/DustbinErrors.hpp"

Dustbin9k::Dustbin9k(const std::string& color, size_t maxWeight)
        : Dustbin(color, maxWeight),
          metalContent(new std::unique_ptr<MetalGarbage>[INITIAL_CAPACITY]),
          bottlecapContent(new std::unique_ptr<BottleCap>[INITIAL_CAPACITY]),
          metalIndex(0),
          bottlecapIndex(0),
          currentMetalCapacity(0),
          currentBottlecapCapacity(0) {}

void Dustbin9k::emptyContents() {
    Dustbin::emptyContents();

    auto newMetalContent =
            std::unique_ptr<std::unique_ptr<MetalGarbage>[]>(
                    new std::unique_ptr<MetalGarbage>[INITIAL_CAPACITY]
            );
    metalContent.swap(newMetalContent);
    metalIndex = 0;
    currentMetalCapacity = INITIAL_CAPACITY;

    auto newBottlecapContent =
            std::unique_ptr<std::unique_ptr<BottleCap>[]>(
                    new std::unique_ptr<BottleCap>[INITIAL_CAPACITY]
            );
    bottlecapContent.swap(newBottlecapContent);
    bottlecapIndex = 0;
    currentBottlecapCapacity = INITIAL_CAPACITY;
}

void Dustbin9k::throwOutMetalGarbage(std::unique_ptr<MetalGarbage>& metalGarbage) {
    if (weight + metalGarbage->weight <= maxWeight) {
        if (metalIndex >= currentMetalCapacity) {
            currentMetalCapacity += CAPACITY_STEP;
            auto newMetalContent =
                    std::unique_ptr<std::unique_ptr<MetalGarbage>[]>(
                            new std::unique_ptr<MetalGarbage>[currentMetalCapacity]
                    );
            for (auto i = 0; i < metalIndex; ++i) newMetalContent[i] = std::move(metalContent[i]);
            metalContent.swap(newMetalContent);
        }
        weight += metalGarbage->weight;
        metalContent[metalIndex++] = std::move(metalGarbage);
    } else {
        throw DustbinIsFull();
    }
}

size_t Dustbin9k::getMetalCount() const {
    return metalIndex;
}

size_t Dustbin9k::getBottlecapCount() const {
    return bottlecapIndex;
}

size_t Dustbin9k::getCurrentMetalCapacity() const {
    return currentMetalCapacity;
}

size_t Dustbin9k::getCurrentBottlecapCapacity() const {
    return currentBottlecapCapacity;
}

void Dustbin9k::throwOutBottleCap(std::unique_ptr<BottleCap>& bottleCap) {
    if (weight + bottleCap->weight <= maxWeight) {
        if (bottleCap->getColor() == "pink") {
            if (bottlecapIndex >= currentBottlecapCapacity) {
                currentBottlecapCapacity += CAPACITY_STEP;
                auto newBottlecapContent =
                        std::unique_ptr<std::unique_ptr<BottleCap>[]>(
                                new std::unique_ptr<BottleCap>[currentBottlecapCapacity]
                        );
                for (auto i = 0; i < bottlecapIndex; ++i) newBottlecapContent[i] = std::move(bottlecapContent[i]);
                bottlecapContent.swap(newBottlecapContent);
            }
            weight += bottleCap->weight;
            bottlecapContent[bottlecapIndex++] = std::move(bottleCap);
        } else {
            throw BottleCapException();
        }
    } else {
        throw DustbinIsFull();
    }
}
