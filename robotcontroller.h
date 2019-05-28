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

    // --- Sensor ---



private:
    MyRobot _myRobot;
    int _speed;

};

#endif // ROBOTCONTROLLER_H
