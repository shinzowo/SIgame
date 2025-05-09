#include "gameUI.h"

GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    infoLabel = new QLabel("Выберите вопрос");
    infoLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(infoLabel);

    gridLayout = new QGridLayout();
    mainLayout->addLayout(gridLayout);

    QPushButton *backButton = new QPushButton("Назад в меню");
    connect(backButton, &QPushButton::clicked, this, &GameWidget::backToMenuRequested);
    mainLayout->addWidget(backButton);
}

void GameWidget::setThemesAndCosts(const QStringList &themes, const QList<int> &costs) {
    // Очистим старые элементы
    QLayoutItem *item;
    while ((item = gridLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    buttonMap.clear();

    // Заголовки тем
    for (int col = 0; col < themes.size(); ++col) {
        QLabel *label = new QLabel(themes[col]);
        label->setAlignment(Qt::AlignCenter);
        gridLayout->addWidget(label, 0, col);
    }

    // Кнопки стоимости
    for (int row = 0; row < costs.size(); ++row) {
        for (int col = 0; col < themes.size(); ++col) {
            int cost = costs[row];
            QPushButton *btn = new QPushButton(QString::number(cost));
            gridLayout->addWidget(btn, row + 1, col);
            buttonMap[btn] = qMakePair(col, cost);
            connect(btn, &QPushButton::clicked, [this, btn]() {
                auto pair = buttonMap[btn];
                emit questionSelected(pair.first, pair.second);
                btn->setEnabled(false); // деактивируем кнопку
            });
        }
    }
}

void GameWidget::disableQuestion(int themeIndex, int cost) {
    for (auto it = buttonMap.begin(); it != buttonMap.end(); ++it) {
        if (it.value().first == themeIndex && it.value().second == cost) {
            it.key()->setEnabled(false);
            return;
        }
    }
}
