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
    gameWidget = new GameWidget(this);

    stackedWidget->addWidget(menuWidget);
    stackedWidget->addWidget(setupWidget);
    stackedWidget->addWidget(gameWidget);

    connect(menuWidget, &MainMenuWidget::startGameRequested, this, &MainWindow::showPlayerSetup);
    connect(menuWidget, &MainMenuWidget::exitRequested, this, &MainWindow::close);
    connect(setupWidget, &PlayerSetupWidget::playersReady, this, &MainWindow::startGame);
    connect(gameWidget, &GameWidget::backToMenuRequested, this, &MainWindow::backToMenu);

}

void MainWindow::showPlayerSetup() {
    stackedWidget->setCurrentWidget(setupWidget);
}

void MainWindow::startGame(QStringList playerNames) {
    // Можно передать список игроков в GameWidget, если нужно
    // gameWidget->initPlayers(playerNames); // если реализовано

    stackedWidget->setCurrentWidget(gameWidget);
}

void MainWindow::backToMenu(){
    stackedWidget->setCurrentWidget(menuWidget);
}

MainWindow::~MainWindow() {
    // Если ничего не нужно удалять вручную, оставь пустым
}



