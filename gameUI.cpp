#include "gameUI.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QInputDialog>

GameWidget::GameWidget(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    //секция игроков
    playersLayout=new QHBoxLayout();
    mainLayout->addLayout(playersLayout);

    //сетка вопросов
    m_gridLayout = new QGridLayout();
    mainLayout->addLayout(m_gridLayout);
}

void GameWidget::setLogic(GameLogic* logic) {
    m_logic = logic;
    players = m_logic->getPlayers();

    // Создаём QLabel для игроков (имя и очки)
        playerNameLabels.clear();
        playerScoreLabels.clear();

        // Очистим предыдущие виджеты в playersLayout (если есть)
        QLayoutItem* child;
        while ((child = playersLayout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }

        for (const Player& p : players) {
            QVBoxLayout* pl = new QVBoxLayout();

            QLabel* nameLabel = new QLabel(p.getName());
            nameLabel->setAlignment(Qt::AlignCenter);
            playerNameLabels.append(nameLabel);

            QLabel* scoreLabel = new QLabel(QString::number(p.getScore()));
            scoreLabel->setAlignment(Qt::AlignCenter);
            playerScoreLabels.append(scoreLabel);

            pl->addWidget(nameLabel);
            pl->addWidget(scoreLabel);

            playersLayout->addLayout(pl);
        }

    displayRound(m_logic->getCurrentRoundIndex());
}

void GameWidget::updatePlayerDisplay() {
    // Обновляем очки игроков на экране
    for (int i = 0; i < players.size(); ++i) {
        playerScoreLabels[i]->setText(QString::number(players[i].getScore()));
    }
}


void GameWidget::displayRound(int roundIndex) {
    if (!m_logic) return;

    clearGrid();
    GameRound round = m_logic->getCurrentRound();

    int themeCount = round.themes.size();
    int questionCount = themeCount > 0 ? round.themes[0].questions.size() : 0;

    questionButtons.clear();
    questionButtons.resize(themeCount);

    // Темы по вертикали в первом столбце
    for (int row = 0; row < themeCount; ++row) {
        QLabel* themeLabel = new QLabel(round.themes[row].name);
        themeLabel->setAlignment(Qt::AlignCenter);
        m_gridLayout->addWidget(themeLabel, row, 0);  // вертикально в 0-й столбец
    }

    // Вопросы — по горизонтали от каждой темы
    for (int row = 0; row < themeCount; ++row) {
        const auto& questions = round.themes[row].questions;
        for (int col = 0; col < questions.size(); ++col) {
            const Question& q = questions[col];

            QPushButton* btn = new QPushButton(QString::number(q.cost));
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            btn->setProperty("theme", row);
            btn->setProperty("index", col);

            connect(btn, &QPushButton::clicked, this, &GameWidget::handleQuestionClicked);

            m_gridLayout->addWidget(btn, row, col + 1);  // вправо от темы
            questionButtons[row].append(btn);
        }
    }
    updatePlayerDisplay();
}


void GameWidget::clearGrid() {
    if (!m_gridLayout) return;

    QLayoutItem* item;
    while ((item = m_gridLayout->takeAt(0)) != nullptr) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }

    questionButtons.clear();
}

void GameWidget::handleQuestionClicked() {
    if (!m_logic) return;

        QPushButton* btn = qobject_cast<QPushButton*>(sender());
        if (!btn) return;

        int themeIndex = btn->property("theme").toInt();
        int questionIndex = btn->property("index").toInt();

        Question q = m_logic->getQuestion(themeIndex, questionIndex);

        // Показываем вопрос
        QString message = QString("Вопрос на %1 очков:\n\n%2").arg(q.cost).arg(q.text);
        QMessageBox::information(this, "Вопрос", message);

        // Временно: просто добавим очки первому игроку как правильно ответившему
        m_logic->applyAnswer(0, true, q.cost);

        btn->setEnabled(false);
        btn->setText("—");
}










