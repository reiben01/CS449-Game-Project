#pragma once
#include <vector>
#include "CellState.h"

class Board {
public:
    explicit Board(int size);
    virtual ~Board() = default;

    void reset();                       // all pegs except the center
    void clear();                       // test helper: empty board
    void setPeg(int r, int c);          // test helper
    int getSize() const { return size_; }
    CellState getState(int r, int c) const;
    bool isValidMove(int fr, int fc, int tr, int tc) const;
    void applyMove(int fr, int fc, int tr, int tc);
    bool hasAnyMove() const;
    int countPegs() const;

protected:
    virtual bool isOnBoard(int r, int c) const = 0;   // the board's shape

private:
    bool inBounds(int r, int c) const;
    int size_;
    std::vector<std::vector<CellState>> cells_;
};