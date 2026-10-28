#include "pch.h"
#include <stdexcept>
#include "SolitaireGame.h"

TEST(SolitaireGameTest, DefaultsAreEnglishAndSeven) {           // AC 1.4
    SolitaireGame game;
    EXPECT_EQ(BoardType::English, game.selectedType());
    EXPECT_EQ(7, game.selectedSize());
}

TEST(SolitaireGameTest, InvalidSizesAreRejected) {              // AC 1.2
    for (const char* s : { "0", "-3", "6", "4", "99", "abc", "", "7x" })
        EXPECT_THROW(SolitaireGame::parseSize(s), std::invalid_argument) << s;
}

TEST(SolitaireGameTest, ValidSizeIsAccepted) {                  // AC 1.1
    EXPECT_EQ(9, SolitaireGame::parseSize("9"));
}

TEST(SolitaireGameTest, SinglePegLeftMeansSolved) {             // AC 4.3
    SolitaireGame game;
    game.board().clear();
    game.board().setPeg(3, 1); game.board().setPeg(3, 2);
    EXPECT_TRUE(game.makeMove(3, 1, 3, 3));
    EXPECT_TRUE(game.isGameOver());
    EXPECT_TRUE(game.isSolved());
}

TEST(SolitaireGameTest, GameOverWhenNoMovesRemain) {            // AC 4.1
    SolitaireGame game;
    game.board().clear();
    game.board().setPeg(3, 0); game.board().setPeg(3, 1); game.board().setPeg(3, 2);
    EXPECT_TRUE(game.makeMove(3, 1, 3, 3));                     // leaves (3,0) and (3,3)
    EXPECT_TRUE(game.isGameOver());
    EXPECT_FALSE(game.isSolved());
}

TEST(SolitaireGameTest, GameContinuesWhileMovesRemain) {        // AC 4.2
    SolitaireGame game;
    game.board().clear();
    game.board().setPeg(3, 0); game.board().setPeg(3, 1);
    game.board().setPeg(3, 2); game.board().setPeg(3, 4);
    EXPECT_TRUE(game.makeMove(3, 1, 3, 3));                     // (3,4) can still jump (3,3)
    EXPECT_FALSE(game.isGameOver());
}

TEST(SolitaireGameTest, NoMovesAfterGameOver) {                 // AC 3.3
    SolitaireGame game;
    game.board().clear();
    game.board().setPeg(3, 1); game.board().setPeg(3, 2);
    game.makeMove(3, 1, 3, 3);                                  // solved, game over
    EXPECT_FALSE(game.makeMove(3, 3, 3, 1));
}

TEST(SolitaireGameTest, SelectedTypeIsUsedForNextGame) {        // AC 1.3
    SolitaireGame game;

    game.setBoardType(BoardType::Diamond);
    game.newGame();
    EXPECT_EQ(BoardType::Diamond, game.selectedType());
    EXPECT_EQ(24, game.board().countPegs());                    // 25 holes minus center
    EXPECT_EQ(CellState::OffBoard, game.board().getState(0, 2)); // Diamond has no hole here

    game.setBoardType(BoardType::Hexagon);
    game.newGame();
    EXPECT_EQ(36, game.board().countPegs());                    // 37 holes minus center

    game.setBoardType(BoardType::English);
    game.newGame();
    EXPECT_EQ(32, game.board().countPegs());                    // 33 holes minus center
    EXPECT_EQ(CellState::Peg, game.board().getState(0, 2));     // English has a hole here
}

TEST(SolitaireGameTest, NewGameDiscardsGameInProgress) {        // AC 2.2
    SolitaireGame game;
    ASSERT_TRUE(game.makeMove(1, 3, 3, 3));                     // play one move
    ASSERT_EQ(31, game.board().countPegs());

    game.newGame();                                             // restart

    EXPECT_EQ(32, game.board().countPegs());                    // fresh board
    EXPECT_EQ(CellState::Empty, game.board().getState(3, 3));   // center empty again
    EXPECT_FALSE(game.isGameOver());
}

TEST(SolitaireGameTest, NewGameAfterGameOverStartsFreshGame) {  // AC 2.2 (finished game)
    SolitaireGame game;
    game.board().clear();
    game.board().setPeg(3, 1); game.board().setPeg(3, 2);
    game.makeMove(3, 1, 3, 3);                                  // solved
    ASSERT_TRUE(game.isGameOver());

    game.newGame();

    EXPECT_FALSE(game.isGameOver());
    EXPECT_FALSE(game.isSolved());
    EXPECT_EQ(32, game.board().countPegs());
}