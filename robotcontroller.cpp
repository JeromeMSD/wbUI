#include "robotcontroller.h"

RobotController::RobotController(MyRobot *robot)
{
    _speed = 0;
}

void RobotController::setSpeed(int value){}

// --- Direction ---
void RobotController::goFront(){}
void RobotController::goBack(){}
void RobotController::turnLeft(bool withFront){}
void RobotController::turnRight(bool withFront){}
