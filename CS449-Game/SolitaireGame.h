#pragma once
#include <memory>
#include <string>
#include "Board.h"
#include "BoardType.h"

class SolitaireGame {
public:
    static constexpr int MinSize = 5, MaxSize = 15, DefaultSize = 7;

    SolitaireGame();
    static bool isValidSize(int s);
    static int parseSize(const std::string& text);   // throws std::invalid_argument

    void setBoardSize(int s);                        // applies on next newGame()
    void setBoardType(BoardType t);
    int selectedSize() const { return selectedSize_; }
    BoardType selectedType() const { return selectedType_; }

    void newGame();
    bool makeMove(int fr, int fc, int tr, int tc);
    bool isGameOver() const { return gameOver_; }
    bool isSolved() const { return gameOver_ && board_->countPegs() == 1; }
    Board& board() { return *board_; }
    const Board& board() const { return *board_; }

private:
    BoardType selectedType_ = BoardType::English;   // default type
    int selectedSize_ = DefaultSize;
    std::unique_ptr<Board> board_;
    bool gameOver_ = false;
};