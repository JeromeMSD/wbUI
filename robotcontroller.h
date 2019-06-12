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
    float getSensorFL();
    float getSensorFR();
    float getSensorBL();
    float getSensorBR();

private:
    MyRobot * _myRobot;
    char _speed;

    /// -- Vars for Sensor --
    int _battery;
    float _sensorFL;                  // Front Left proximity sensor
    float _sensorFR;                  // Front Right proximity sensor
    float _sensorBL;                  // Back Left proximity sensor
    float _sensorBR;                  // Back Right proximity sensor

    // Functions
    float distanceConversion(int sensorVal);

};

#endif // ROBOTCONTROLLER_H
