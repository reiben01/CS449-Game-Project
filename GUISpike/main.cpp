#include <QApplication>
#include "SolitaireWindow.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	SolitaireWindow window;
	window.setWindowTitle("CS449-Game");
	window.resize(650, 700);
	window.show();
	return app.exec();
}