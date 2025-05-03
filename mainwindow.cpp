#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800, 600);
    setWindowTitle("Своя игра");

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    menuWidget = new MainMenuWidget(this);
    setupWidget = new PlayerSetupWidget(this);

    stackedWidget->addWidget(menuWidget);
    stackedWidget->addWidget(setupWidget);

    connect(menuWidget, &MainMenuWidget::startGameRequested, this, &MainWindow::showPlayerSetup);
    connect(menuWidget, &MainMenuWidget::exitRequested, this, &MainWindow::close);

}

void MainWindow::showPlayerSetup() {
    stackedWidget->setCurrentWidget(setupWidget);
}

MainWindow::~MainWindow() {
    // Если ничего не нужно удалять вручную, оставь пустым
}



