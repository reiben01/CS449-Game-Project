#pragma once
#include "Board.h"

class EnglishBoard : public Board {
public:
    explicit EnglishBoard(int size) : Board(size) {}
protected:
    bool isOnBoard(int r, int c) const override {
        int n = getSize(), corner = n / 3;
        return (r >= corner && r < n - corner) || (c >= corner && c < n - corner);
    }
};