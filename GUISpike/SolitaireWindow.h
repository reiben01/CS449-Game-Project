#pragma once
#include <QWidget>
#include "SolitaireGame.h"
class QLineEdit; class QLabel; class BoardWidget;

class SolitaireWindow : public QWidget {
    Q_OBJECT
public:
    explicit SolitaireWindow(QWidget* parent = nullptr);
private slots:
    void onNewGame();
private:
    SolitaireGame game_;
    QLineEdit* sizeEdit_;
    QLabel* status_;
    BoardWidget* boardWidget_;
};