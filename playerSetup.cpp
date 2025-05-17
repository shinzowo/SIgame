#include "playerSetup.h".h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QScrollArea>

PlayerSetupWidget::PlayerSetupWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Введите имена игроков:");
    mainLayout->addWidget(label);

    // Секция для игроков
    playersLayout = new QVBoxLayout();
    mainLayout->addLayout(playersLayout);

    // Добавляем первого игрока по умолчанию
    onAddPlayerClicked();

    addPlayerButton = new QPushButton("Добавить игрока");
    mainLayout->addWidget(addPlayerButton);
    connect(addPlayerButton, &QPushButton::clicked, this, &PlayerSetupWidget::onAddPlayerClicked);

    // Кнопка выбора файла вопросов
    loadButton = new QPushButton("Загрузить пакет вопросов");
    fileLabel = new QLabel("Файл не выбран");

    mainLayout->addWidget(loadButton);
    mainLayout->addWidget(fileLabel);

    startButton = new QPushButton("Начать игру");
    mainLayout->addWidget(startButton);

    connect(loadButton, &QPushButton::clicked, this, &PlayerSetupWidget::onLoadQuestionsClicked);
    connect(startButton, &QPushButton::clicked, this, &PlayerSetupWidget::onStartClicked);
}

void PlayerSetupWidget::onAddPlayerClicked() {
    QLineEdit *edit = new QLineEdit(this);
    edit->setPlaceholderText("Имя игрока");
    playerEdits.append(edit);
    playersLayout->addWidget(edit);
}

void PlayerSetupWidget::onLoadQuestionsClicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл с вопросами", "", "JSON Files (*.json);;All Files (*)");
    if (!filePath.isEmpty()) {
        loadedFilePath = filePath;
        fileLabel->setText("Выбран файл: " + QFileInfo(filePath).fileName());
        emit questionsLoaded(filePath);
    }
}

void PlayerSetupWidget::onStartClicked() {
    QStringList names;
    for (QLineEdit *edit : playerEdits) {
        QString name = edit->text().trimmed();
        if (!name.isEmpty()) names << name;
    }

    if (names.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите хотя бы одного игрока.");
        return;
    }

    if (loadedFilePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Выберите пакет вопросов.");
        return;
    }

    emit playersReady(names, loadedFilePath);
}
