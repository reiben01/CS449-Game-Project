#pragma once
#include <memory>
#include "Board.h"
#include "BoardType.h"
std::unique_ptr<Board> createBoard(BoardType type, int size);