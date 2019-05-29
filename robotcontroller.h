#ifndef ROBOTCONTROLLER_H
#define ROBOTCONTROLLER_H

#include "MYROBOT.h"

class RobotController
{
public:
    RobotController(MyRobot *myRobot);
    ~RobotController();

    void setSpeed(int value);

    // --- Direction ---
    void goFront();
    void goBack();
    void turnLeft(bool withFront);
    void turnRight(bool withFront);
    void stop();

    // --- Sensor ---
    void getCamStream();


private:
    MyRobot * _myRobot;
    char _speed;

};

#endif // ROBOTCONTROLLER_H
