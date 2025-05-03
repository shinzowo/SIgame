#include "menu.h"

MainMenuWidget::MainMenuWidget(QWidget *parent):QWidget(parent){
    QVBoxLayout *layout = new QVBoxLayout(this);
       layout->setAlignment(Qt::AlignCenter);

       QPushButton *startBtn = new QPushButton("Игра");
       QPushButton *exitBtn = new QPushButton("Выход");

       startBtn->setFixedSize(400, 60);
       exitBtn->setFixedSize(400, 60);

       QFont font("Arial", 16);
       startBtn->setFont(font);
       exitBtn->setFont(font);

       QString style = R"(
           QPushButton {
               background-color: #3498db;
               color: white;
               border-radius: 10px;
           }
           QPushButton:hover {
               background-color: #2980b9;
           }
           QPushButton:pressed {
               background-color: #1f618d;
           }
       )";

       startBtn->setStyleSheet(style);
       exitBtn->setStyleSheet(style);

       layout->addWidget(startBtn);
       layout->addSpacing(100);
       layout->addWidget(exitBtn);

       connect(startBtn, &QPushButton::clicked, this, &MainMenuWidget::startGameRequested);
       connect(exitBtn, &QPushButton::clicked, this, &MainMenuWidget::exitRequested);
}
