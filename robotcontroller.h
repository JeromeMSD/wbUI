#ifndef ROBOTCONTROLLER_H
#define ROBOTCONTROLLER_H

#include "MYROBOT.h"

class RobotController
{
public:
    RobotController();
    ~RobotController();

    // --- Connection ---
    void startConnection();
    void endConnection();

    void setSpeed(int value);

    // --- Direction ---
    void goFront();
    void goBack();
    void turnLeft(bool withFront);
    void turnRight(bool withFront);
    void stop();

    // --- Sensor ---
    void getData();                 // HardWare recuperation method

    QString getCamStream();
    int getBattery();
    int getSensorFL();
    int getSensorFR();
    int getSensorBL();
    int getSensorBR();

private:
    MyRobot * _myRobot;
    char _speed;

    /// -- Vars for Sensor --
    int _battery;
    int _sensorFL;                  // Front Left proximity sensor
    int _sensorFR;                  // Front Right proximity sensor
    int _sensorBL;                  // Back Left proximity sensor
    int _sensorBR;                  // Back Right proximity sensor

};

#endif // ROBOTCONTROLLER_H
