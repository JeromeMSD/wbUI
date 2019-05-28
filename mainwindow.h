#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSlider>

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

private slots:
    void startConnection();
    void handleSlider();
    void setBatteryBar(int value);
    void go(int way);

    void on_front_clicked();

    void on_frontRight_clicked();

    void on_frontLeft_clicked();

    void on_left_clicked();

    void on_right_clicked();

    void on_back_clicked();

private:
    Ui::MainWindow *ui;

    /// --- Working variables ---
    MyRobot *wifiBot;
    RobotController *rbController;
};

#endif // MAINWINDOW_H
