#ifndef GAMEUI_H
#define GAMEUI_H
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QMap>

class GameWidget : public QWidget {
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);
    void setThemesAndCosts(const QStringList &themes, const QList<int> &costs);
    void disableQuestion(int themeIndex, int cost);


signals:
    void questionSelected(int themeIndex, int cost);
    void backToMenuRequested();

private:
    QGridLayout *gridLayout;
    QMap<QPushButton*, QPair<int, int>> buttonMap; // кнопка → (тема, цена)
    QLabel *infoLabel;
};
#endif // GAMEUI_H
