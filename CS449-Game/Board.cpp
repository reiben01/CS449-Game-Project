#include "Board.h"
#include <cstdlib>
Board::Board(int size)
    : size_(size), cells_(size, std::vector<CellState>(size, CellState::OffBoard)) {
}

bool Board::inBounds(int r, int c) const { return r >= 0 && r < size_ && c >= 0 && c < size_; }

void Board::reset() {
    for (int r = 0; r < size_; ++r)
        for (int c = 0; c < size_; ++c)
            cells_[r][c] = isOnBoard(r, c) ? CellState::Peg : CellState::OffBoard;
    cells_[size_ / 2][size_ / 2] = CellState::Empty;
}

void Board::clear() {
    for (int r = 0; r < size_; ++r)
        for (int c = 0; c < size_; ++c)
            cells_[r][c] = isOnBoard(r, c) ? CellState::Empty : CellState::OffBoard;
}

void Board::setPeg(int r, int c) { if (inBounds(r, c) && isOnBoard(r, c)) cells_[r][c] = CellState::Peg; }

CellState Board::getState(int r, int c) const {
    return inBounds(r, c) ? cells_[r][c] : CellState::OffBoard;
}

bool Board::isValidMove(int fr, int fc, int tr, int tc) const {
    int dr = tr - fr, dc = tc - fc;
    bool straightJump = (std::abs(dr) == 2 && dc == 0) || (std::abs(dc) == 2 && dr == 0);
    if (!straightJump) return false;
    return getState(fr, fc) == CellState::Peg
        && getState(fr + dr / 2, fc + dc / 2) == CellState::Peg
        && getState(tr, tc) == CellState::Empty;
}

void Board::applyMove(int fr, int fc, int tr, int tc) {   // caller checks isValidMove first
    cells_[fr][fc] = CellState::Empty;
    cells_[(fr + tr) / 2][(fc + tc) / 2] = CellState::Empty;
    cells_[tr][tc] = CellState::Peg;
}

bool Board::hasAnyMove() const {
    static const int dirs[4][2] = { {-2, 0}, {2, 0}, {0, -2}, {0, 2} };
    for (int r = 0; r < size_; ++r)
        for (int c = 0; c < size_; ++c)
            for (const auto& d : dirs)
                if (isValidMove(r, c, r + d[0], c + d[1])) return true;
    return false;
}

int Board::countPegs() const {
    int n = 0;
    for (const auto& row : cells_) for (CellState s : row) if (s == CellState::Peg) ++n;
    return n;
}