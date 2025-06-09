#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    
    // Connect the close button to our slot
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onCloseButtonClicked() {
    close();
}
