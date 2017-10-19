#include "../../include/garbage/PaperGarbage.h"

PaperGarbage::PaperGarbage(const std::string& name) : Garbage(name), isSqueezed(false) {}

void PaperGarbage::squeeze() {
    isSqueezed = true;
}

bool PaperGarbage::IsSqueezed() const {
    return isSqueezed;
}
