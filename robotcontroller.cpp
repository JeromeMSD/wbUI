#include "robotcontroller.h"

// Constructor
RobotController::RobotController()
{
    _myRobot = new MyRobot();
    _speed = 0;
    _sensorL;
    _sensorR;
}

RobotController::~RobotController(){
    delete _myRobot;
}

void RobotController::setSpeed(int value){   _speed = value;  }

// --- Connection ---
void RobotController::startConnection(){
    _myRobot->doConnect();
}

void RobotController::endConnection(){
    _myRobot->disConnect();
}




// --- Direction ---

void RobotController::goFront(){
    _myRobot->speed(_speed,_speed,true,true);
}

void RobotController::goBack(){
    _myRobot->speed(_speed,_speed,false,false);
}

void RobotController::turnLeft(bool withFront){
    if (withFront) {
        _myRobot->speed(_speed,_speed-50,true,true);
    }else
        _myRobot->speed(_speed,_speed,true,false);
}

void RobotController::turnRight(bool withFront){
    if(withFront){
        _myRobot->speed(_speed-50,_speed,true,true);
    }else
        _myRobot->speed(_speed,_speed,false,true);
}

void RobotController::stop(){
    _myRobot->speed(0,0,true,true);
}


/// --- Sensor ---

void RobotController::getCamStream(){

}

void RobotController::getData(){
    QByteArray data;
    data = getDataReceive();
    _battery = data[2];

}




