#pragma once
#include <cstdlib>
#include "Board.h"

class HexagonBoard : public Board {
public:
    explicit HexagonBoard(int size) : Board(size) {}
protected:
    bool isOnBoard(int r, int c) const override {
        int c0 = getSize() / 2;                                       // center index
        return std::abs(r - c0) + std::abs(c - c0) <= c0 + c0 / 2;    // square with cut corners
    }
};