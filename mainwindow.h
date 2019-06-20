#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QKeyEvent>
#include <QWidget>
#include<QWebEngineView>
#include <QtGui>

//#include <QWebEngineView>

#include "MYROBOT.h"
#include "robotcontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init();
    static void writeConsole(char* text);

protected:
    /// --- KeyEvent ---
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

private slots:
    void startConnection();
    void handleSlider();

    void on_front_pressed();
    void on_left_pressed();
    void on_right_pressed();
    void on_back_pressed();

    void on_front_released();
    void on_right_released();
    void on_left_released();
    void on_back_released();

private:
    Ui::MainWindow *ui;

    /// --- Working variables ---
    RobotController *rbController;
    //QWebEngineView *view;

    void refreshUI();
    void changeState(int state);
    void setBatteryBar(int value);
    void go(int way);
};

#endif // MAINWINDOW_H
