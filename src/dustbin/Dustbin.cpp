#include "../../include/dustbin/Dustbin.h"
#include "../../include/dustbin/DustbinErrors.hpp"

Dustbin::Dustbin(const std::string& color, size_t maxWeight)
        : color(color),
          maxWeight(maxWeight),
          weight(0),
          paperContent(new std::unique_ptr<PaperGarbage>[INITIAL_CAPACITY]),
          plasticContent(new std::unique_ptr<PlasticGarbage>[INITIAL_CAPACITY]),
          houseWasteContent(new std::unique_ptr<Garbage>[INITIAL_CAPACITY]),
          garbageIndex(0),
          paperIndex(0),
          plasticIndex(0),
          currentGarbageCapacity(INITIAL_CAPACITY),
          currentPaperCapacity(INITIAL_CAPACITY),
          currentPlasticCapacity(INITIAL_CAPACITY) {}

void Dustbin::throwOutGarbage(std::unique_ptr<Garbage>& garbage) {
    if (weight + garbage->weight <= maxWeight) {
        if (garbageIndex >= currentGarbageCapacity) {
            currentGarbageCapacity += CAPACITY_STEP;
            auto newHouseWasteContent =
                    std::unique_ptr<std::unique_ptr<Garbage>[]>(
                            new std::unique_ptr<Garbage>[currentGarbageCapacity]
                    );
            for (auto i = 0; i < garbageIndex; ++i) newHouseWasteContent[i] = std::move(houseWasteContent[i]);
            houseWasteContent.swap(newHouseWasteContent);
        }
        weight += garbage->weight;
        houseWasteContent[garbageIndex++] = std::move(garbage);
    } else {
        throw DustbinIsFull();
    }
}

void Dustbin::throwOutPaperGarbage(std::unique_ptr<PaperGarbage>& paperGarbage) {
    if (weight + paperGarbage->weight <= maxWeight) {
        if (paperGarbage->IsSqueezed()) {
            if (paperIndex >= currentPaperCapacity) {
                currentPaperCapacity += CAPACITY_STEP;
                auto newPaperContent =
                        std::unique_ptr<std::unique_ptr<PaperGarbage>[]>(
                                new std::unique_ptr<PaperGarbage>[currentPaperCapacity]
                        );
                for (auto i = 0; i < paperIndex; ++i) newPaperContent[i] = std::move(paperContent[i]);
                paperContent.swap(newPaperContent);
            }
            weight += paperGarbage->weight;
            paperContent[paperIndex++] = std::move(paperGarbage);
        } else {
            throw DustbinContentError();
        }
    } else {
        throw DustbinIsFull();
    }
}

void Dustbin::throwOutPlasticGarbage(std::unique_ptr<PlasticGarbage>& plasticGarbage) {
    if (weight + plasticGarbage->weight <= maxWeight) {
        if (plasticGarbage->IsClean()) {
            if (plasticIndex >= currentPlasticCapacity) {
                currentPlasticCapacity += CAPACITY_STEP;
                auto newPlasticContent =
                        std::unique_ptr<std::unique_ptr<PlasticGarbage>[]>(
                                new std::unique_ptr<PlasticGarbage>[currentPlasticCapacity]
                        );
                for (auto i = 0; i < plasticIndex; ++i) newPlasticContent[i] = std::move(plasticContent[i]);
                plasticContent.swap(newPlasticContent);
            }
            weight += plasticGarbage->weight;
            plasticContent[plasticIndex++] = std::move(plasticGarbage);
        } else {
            throw DustbinContentError();
        }
    } else {
        throw DustbinIsFull();
    }
}

void Dustbin::emptyContents() {
    weight = 0;
    auto newHouseWasteContent =
            std::unique_ptr<std::unique_ptr<Garbage>[]>(
                    new std::unique_ptr<Garbage>[INITIAL_CAPACITY]
            );
    houseWasteContent.swap(newHouseWasteContent);
    garbageIndex = 0;
    currentGarbageCapacity = INITIAL_CAPACITY;

    auto newPaperContent =
            std::unique_ptr<std::unique_ptr<PaperGarbage>[]>(
                    new std::unique_ptr<PaperGarbage>[INITIAL_CAPACITY]
            );
    paperContent.swap(newPaperContent);
    paperIndex = 0;
    currentPaperCapacity = INITIAL_CAPACITY;

    auto newPlasticContent =
            std::unique_ptr<std::unique_ptr<PlasticGarbage>[]>(
                    new std::unique_ptr<PlasticGarbage>[INITIAL_CAPACITY]
            );
    plasticContent.swap(newPlasticContent);
    plasticIndex = 0;
    currentPlasticCapacity = INITIAL_CAPACITY;
}

const std::string& Dustbin::getColor() const {
    return color;
}

size_t Dustbin::getGarbageCount() const {
    return garbageIndex;
}

size_t Dustbin::getPaperCount() const {
    return paperIndex;
}

size_t Dustbin::getPlasticCount() const {
    return plasticIndex;
}

size_t Dustbin::getCurrentGarbageCapacity() const {
    return currentGarbageCapacity;
}

size_t Dustbin::getCurrentPaperCapacity() const {
    return currentPaperCapacity;
}

size_t Dustbin::getCurrentPlasticCapacity() const {
    return currentPlasticCapacity;
}

bool Dustbin::isEmpty() const {
    return weight == 0;
}
