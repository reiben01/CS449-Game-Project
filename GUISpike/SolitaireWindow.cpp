#include "SolitaireWindow.h"
#include "BoardWidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <stdexcept>
SolitaireWindow::SolitaireWindow(QWidget* parent) : QWidget(parent) {
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel("Welcome to Peg Solitaire!"));

    sizeEdit_ = new QLineEdit(QString::number(SolitaireGame::DefaultSize));
    sizeEdit_->setMaximumWidth(60);
    auto* english = new QRadioButton("English");
    auto* hexagon = new QRadioButton("Hexagon");
    auto* diamond = new QRadioButton("Diamond");
    english->setChecked(true);                                   // default type
    auto* newGameBtn = new QPushButton("New Game");

    auto* top = new QHBoxLayout();
    top->addWidget(new QLabel("Board size")); top->addWidget(sizeEdit_);
    top->addWidget(new QLabel("Board Type"));
    top->addWidget(english); top->addWidget(hexagon); top->addWidget(diamond);
    top->addWidget(newGameBtn); top->addStretch();
    mainLayout->addLayout(top);

    boardWidget_ = new BoardWidget(game_, this);
    mainLayout->addWidget(boardWidget_, 1);
    status_ = new QLabel("Choose settings and click New Game.");
    mainLayout->addWidget(status_);

    connect(english, &QRadioButton::clicked, this, [this] { game_.setBoardType(BoardType::English); });
    connect(hexagon, &QRadioButton::clicked, this, [this] { game_.setBoardType(BoardType::Hexagon); });
    connect(diamond, &QRadioButton::clicked, this, [this] { game_.setBoardType(BoardType::Diamond); });
    connect(newGameBtn, &QPushButton::clicked, this, &SolitaireWindow::onNewGame);
    connect(boardWidget_, &BoardWidget::statusChanged, status_, &QLabel::setText);
}

void SolitaireWindow::onNewGame() {
    try {
        game_.setBoardSize(SolitaireGame::parseSize(sizeEdit_->text().toStdString()));
    }
    catch (const std::invalid_argument& ex) {
        status_->setText(QString("Error: ") + ex.what());           // no new game starts
        sizeEdit_->setText(QString::number(game_.selectedSize()));  // last valid size stays
        return;
    }
    game_.newGame();
    boardWidget_->clearSelection();
    status_->setText("New game started. Click a peg, then an empty hole.");
    boardWidget_->update();
}