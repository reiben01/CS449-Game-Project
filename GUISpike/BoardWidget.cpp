#include "BoardWidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <algorithm>
BoardWidget::BoardWidget(SolitaireGame& game, QWidget* parent) : QWidget(parent), game_(game) {
    setMinimumSize(420, 420);
}

int BoardWidget::cellSize() const { return std::min(width(), height()) / game_.board().getSize(); }

QString BoardWidget::endMessage() const {
    if (!game_.isGameOver()) return "Move made.";
    return game_.isSolved() ? "You solved the puzzle! One peg left."
        : "Game over: no moves are left.";
}

void BoardWidget::mousePressEvent(QMouseEvent* e) {
    int cs = cellSize(); if (cs <= 0) return;
    int r = e->pos().y() / cs, c = e->pos().x() / cs;
    const Board& b = game_.board();

    if (game_.isGameOver()) { emit statusChanged("Game is over. Click New Game to play again."); return; }

    if (b.getState(r, c) == CellState::Peg) {
        selR_ = r; selC_ = c;
        emit statusChanged("Peg selected. Click an empty hole to jump.");
    }
    else if (selR_ >= 0 && b.getState(r, c) == CellState::Empty) {
        emit statusChanged(game_.makeMove(selR_, selC_, r, c) ? endMessage() : "Invalid move.");
        clearSelection();
    }
    else {
        emit statusChanged("Invalid move.");
        clearSelection();
    }
    update();
}
void BoardWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    const Board& b = game_.board();
    int cs = cellSize(), pad = cs / 6, d = cs - 2 * pad;
    for (int r = 0; r < b.getSize(); ++r)
        for (int c = 0; c < b.getSize(); ++c) {
            CellState s = b.getState(r, c);
            if (s == CellState::OffBoard) continue;
            p.setBrush(Qt::lightGray); p.setPen(Qt::NoPen);
            p.drawEllipse(c * cs + pad, r * cs + pad, d, d);                  // hole
            if (s == CellState::Peg) {
                p.setBrush(r == selR_ && c == selC_ ? QColor(Qt::darkYellow) : QColor(Qt::blue));
                p.drawEllipse(c * cs + pad + 4, r * cs + pad + 4, d - 8, d - 8); // peg
            }
        }
}