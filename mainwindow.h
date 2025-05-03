#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "menu.h"
#include "playerSetup.h"

#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MainMenuWidget *menuWidget;
    PlayerSetupWidget *setupWidget;
    QStackedWidget *stackedWidget;
private slots:
    void showPlayerSetup();

};
#endif // MAINWINDOW_H
