#include <QApplication>
#include "mainwindow/mainwindow.h"
#include "include/toml.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    MainWindow window;
    window.show();
    
    return app.exec();
}
