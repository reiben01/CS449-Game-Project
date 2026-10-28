#include "SolitaireGame.h"
#include "BoardFactory.h"
#include <cctype>
#include <stdexcept>

SolitaireGame::SolitaireGame() { newGame(); }

bool SolitaireGame::isValidSize(int s) { return s >= MinSize && s <= MaxSize && s % 2 == 1; }

int SolitaireGame::parseSize(const std::string& text) {
    int value = 0; std::size_t pos = 0;
    try { value = std::stoi(text, &pos); }
    catch (const std::exception&) { throw std::invalid_argument("Board size must be a number."); }
    while (pos < text.size() && std::isspace(static_cast<unsigned char>(text[pos]))) ++pos;
    if (pos != text.size()) throw std::invalid_argument("Board size must be a number.");
    if (!isValidSize(value))
        throw std::invalid_argument("Board size must be odd, from 5 to 15.");
    return value;
}

void SolitaireGame::setBoardSize(int s) {
    if (!isValidSize(s)) throw std::invalid_argument("Invalid board size.");
    selectedSize_ = s;
}
void SolitaireGame::setBoardType(BoardType t) { selectedType_ = t; }

void SolitaireGame::newGame() {
    board_ = createBoard(selectedType_, selectedSize_);
    gameOver_ = false;
}

bool SolitaireGame::makeMove(int fr, int fc, int tr, int tc) {
    if (gameOver_ || !board_->isValidMove(fr, fc, tr, tc)) return false;
    board_->applyMove(fr, fc, tr, tc);
    gameOver_ = board_->countPegs() == 1 || !board_->hasAnyMove();
    return true;
}