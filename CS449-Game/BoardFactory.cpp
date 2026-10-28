#include "BoardFactory.h"
#include "EnglishBoard.h"
#include "HexagonBoard.h"
#include "DiamondBoard.h"

std::unique_ptr<Board> createBoard(BoardType type, int size) {
    std::unique_ptr<Board> b;
    switch (type) {
    case BoardType::Hexagon: b = std::make_unique<HexagonBoard>(size); break;
    case BoardType::Diamond: b = std::make_unique<DiamondBoard>(size); break;
    default:                 b = std::make_unique<EnglishBoard>(size); break;
    }
    b->reset();
    return b;
}