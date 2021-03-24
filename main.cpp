#include <QApplication>

#include "NodeEditorWindow.h"

#include <iostream>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    NodeEditorWindow window;

    return app.exec();
}
