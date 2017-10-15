#include "../include/Dustbin.h"
#include "../include/DustbinErrors.hpp"

Dustbin::Dustbin(const std::string& color)
        : color(color),
          paperContent(new std::unique_ptr<PaperGarbage>[INITIAL_CAPACITY]),
          plasticContent(new std::unique_ptr<PlasticGarbage>[INITIAL_CAPACITY]),
          houseWasteContent(new std::unique_ptr<Garbage>[INITIAL_CAPACITY]),
          garbageIndex(0),
          paperIndex(0),
          plasticIndex(0),
          garbageCurrentCapacity(INITIAL_CAPACITY),
          paperCurrentCapacity(INITIAL_CAPACITY),
          plasticCurrentCapacity(INITIAL_CAPACITY) {}

void Dustbin::throwOutGarbage(std::unique_ptr<Garbage>& garbage) {
    if (garbageIndex >= garbageCurrentCapacity) {
        garbageCurrentCapacity += CAPACITY_STEP;
        auto newHouseWasteContent =
                std::unique_ptr<std::unique_ptr<Garbage>[]>(
                        new std::unique_ptr<Garbage>[garbageCurrentCapacity]
                );
        for (auto i = 0; i < garbageIndex; ++i) newHouseWasteContent[i] = std::move(houseWasteContent[i]);
        houseWasteContent.swap(newHouseWasteContent);
    }
    houseWasteContent[garbageIndex++] = std::move(garbage);
}

void Dustbin::throwOutPaperGrabage(std::unique_ptr<PaperGarbage>& paperGarbage) {
    if (paperGarbage->IsSqueezed()) {
        if (paperIndex >= paperCurrentCapacity) {
            paperCurrentCapacity += CAPACITY_STEP;
            auto newPaperContent =
                    std::unique_ptr<std::unique_ptr<PaperGarbage>[]>(
                            new std::unique_ptr<PaperGarbage>[paperCurrentCapacity]
                    );
            for (auto i = 0; i < paperIndex; ++i) newPaperContent[i] = std::move(paperContent[i]);
            paperContent.swap(newPaperContent);
        }
        paperContent[paperIndex++] = std::move(paperGarbage);
    } else {
        throw DustbinContentError();
    }
}

void Dustbin::throwOutPlasticGarbage(std::unique_ptr<PlasticGarbage>& plasticGarbage) {
    if (plasticGarbage->IsClean()) {
        if (plasticIndex >= plasticCurrentCapacity) {
            plasticCurrentCapacity += CAPACITY_STEP;
            auto newPlasticContent =
                    std::unique_ptr<std::unique_ptr<PlasticGarbage>[]>(
                            new std::unique_ptr<PlasticGarbage>[plasticCurrentCapacity]
                    );
            for (auto i = 0; i < plasticIndex; ++i) newPlasticContent[i] = std::move(plasticContent[i]);
            plasticContent.swap(newPlasticContent);
        }
        plasticContent[plasticIndex++] = std::move(plasticGarbage);
    } else {
        throw DustbinContentError();
    }
}

void Dustbin::emptyContents() {
    auto newHouseWasteContent =
            std::unique_ptr<std::unique_ptr<Garbage>[]>(
                    new std::unique_ptr<Garbage>[INITIAL_CAPACITY]
            );
    houseWasteContent.swap(newHouseWasteContent);
    garbageIndex = 0;
    garbageCurrentCapacity = INITIAL_CAPACITY;

    auto newPaperContent =
            std::unique_ptr<std::unique_ptr<PaperGarbage>[]>(
                    new std::unique_ptr<PaperGarbage>[INITIAL_CAPACITY]
            );
    paperContent.swap(newPaperContent);
    paperIndex = 0;
    paperCurrentCapacity = INITIAL_CAPACITY;

    auto newPlasticContent =
            std::unique_ptr<std::unique_ptr<PlasticGarbage>[]>(
                    new std::unique_ptr<PlasticGarbage>[INITIAL_CAPACITY]
            );
    plasticContent.swap(newPlasticContent);
    plasticIndex = 0;
    plasticCurrentCapacity = INITIAL_CAPACITY;
}
