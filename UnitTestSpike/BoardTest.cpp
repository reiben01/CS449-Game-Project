#include "pch.h"
#include "BoardFactory.h"

TEST(BoardTest, NewBoardHasCenterEmptyAndRestPegs) {            // AC 2.1
    auto b = createBoard(BoardType::English, 7);
    EXPECT_EQ(CellState::Empty, b->getState(3, 3));
    EXPECT_EQ(32, b->countPegs());                              // 33 holes minus center
}

TEST(BoardTest, ValidJumpMovesPegAndRemovesJumped) {            // AC 3.1
    auto b = createBoard(BoardType::English, 7);
    ASSERT_TRUE(b->isValidMove(1, 3, 3, 3));
    b->applyMove(1, 3, 3, 3);
    EXPECT_EQ(CellState::Empty, b->getState(1, 3));
    EXPECT_EQ(CellState::Empty, b->getState(2, 3));
    EXPECT_EQ(CellState::Peg, b->getState(3, 3));
    EXPECT_EQ(31, b->countPegs());
}

TEST(BoardTest, InvalidMovesAreRejected) {                      // AC 3.2
    auto b = createBoard(BoardType::English, 7);
    EXPECT_FALSE(b->isValidMove(2, 2, 2, 4));   // lands on a filled hole
    EXPECT_FALSE(b->isValidMove(1, 3, 3, 5));   // diagonal
    EXPECT_FALSE(b->isValidMove(0, 0, 0, 2));   // off the board
    EXPECT_EQ(32, b->countPegs());              // board unchanged
}