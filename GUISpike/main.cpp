#include "GUISpike.h"
#include <QtWidgets/QApplication>
#include <QApplication>
#include <QCheckBox>
#include <QFrame>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	QWidget window;
	window.setWindowTitle("CS449-Game");

	auto* mainLayout = new QVBoxLayout(&window);

	auto* title = new QLabel("Welcome to Peg Solitaire!");
	mainLayout->addWidget(title);

	auto* boardSizeLabel = new QLabel("Board size: 67");
	mainLayout->addWidget(boardSizeLabel);

	auto* hLine = new QFrame();
	hLine->setFrameShape(QFrame::HLine);
	hLine->setFrameShadow(QFrame::Sunken);
	mainLayout->addWidget(hLine);

	auto* boardTypeBox = new QGroupBox("Board Type");
	auto* radioLayout = new QVBoxLayout();
	auto* englishRadio = new QRadioButton("English");
	auto* hexagonRadio = new QRadioButton("Hexagon");
	auto* diamondRadio = new QRadioButton("Diamond");
	auto* squareRadio = new QRadioButton("Square");

	englishRadio->setChecked(true);
	radioLayout->addWidget(englishRadio);
	radioLayout->addWidget(hexagonRadio);
	radioLayout->addWidget(diamondRadio);
	radioLayout->addWidget(squareRadio);
	boardTypeBox->setLayout(radioLayout);
	mainLayout->addWidget(boardTypeBox);

	auto* row = new QHBoxLayout();
	auto* vLine = new QFrame();
	vLine->setFrameShape(QFrame::VLine);
	vLine->setFrameShadow(QFrame::Sunken);
	
	auto* recordCheckbox = new QCheckBox("Record game");
	recordCheckbox->setChecked(true);

	row->addWidget(new QLabel("Settings:"));
	row->addWidget(vLine);
	row->addWidget(recordCheckbox);
	mainLayout->addLayout(row);

	window.setLayout(mainLayout);
	window.resize(300, 300);
	window.show();

	return app.exec();
}