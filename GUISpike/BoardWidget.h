#pragma once
#include <QWidget>
#include "SolitaireGame.h"

class BoardWidget : public QWidget {
    Q_OBJECT
public:
    explicit BoardWidget(SolitaireGame& game, QWidget* parent = nullptr);
    void clearSelection() { selR_ = selC_ = -1; }
signals:
    void statusChanged(const QString& message);
protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent* event) override;
private:
    int cellSize() const;
    QString endMessage() const;
    SolitaireGame& game_;
    int selR_ = -1, selC_ = -1;
};