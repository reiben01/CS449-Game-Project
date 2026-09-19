#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUISpike.h"

class GUISpike : public QMainWindow
{
    Q_OBJECT

public:
    GUISpike(QWidget *parent = nullptr);
    ~GUISpike();

private:
    Ui::GUISpikeClass ui;
};

