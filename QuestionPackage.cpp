#include "QuestionPackage.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QuestionPackage::QuestionPackage() {}

bool QuestionPackage::loadFromFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    if (error.error != QJsonParseError::NoError)
        return false;

    QJsonObject rootObj = doc.object();
    QJsonArray roundsArray = rootObj["rounds"].toArray();

    rounds.clear();

    for (const QJsonValue &roundVal : roundsArray) {
        QJsonObject roundObj = roundVal.toObject();
        GameRound round;
        round.name = roundObj["name"].toString();

        QJsonArray themesArray = roundObj["themes"].toArray();
        for (const QJsonValue &themeVal : themesArray) {
            QJsonObject themeObj = themeVal.toObject();
            Theme theme;
            theme.name = themeObj["name"].toString();

            QJsonArray questionsArray = themeObj["questions"].toArray();
            for (const QJsonValue &qVal : questionsArray) {
                QJsonObject qObj = qVal.toObject();
                Question q;
                q.cost = qObj["cost"].toInt();
                q.text = qObj["text"].toString();
                q.answer = qObj["answer"].toString();
                q.type = qObj.contains("type") ? qObj["type"].toString() : "standard";
                theme.questions.append(q);
            }

            round.themes.append(theme);
        }

        rounds.append(round);
    }

    return true;
}

QList<GameRound> QuestionPackage::getRounds() const {
    return rounds;
}

GameRound QuestionPackage::getRound(int index) const {
    if (index >= 0 && index < rounds.size())
        return rounds[index];
    return GameRound(); // Пустой раунд
}

int QuestionPackage::getRoundCount() const {
    return rounds.size();
}
