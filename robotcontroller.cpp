#include "robotcontroller.h"

#include <iostream>
#include <QString>

using namespace :: std;

// Constructor
RobotController::RobotController()
{
    _myRobot = new MyRobot();
    _speed = 0;
    _battery = 0;
    _sensorFL = 0;
    _sensorFR = 0;
    _sensorBL = 0;
    _sensorBR = 0;
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

void RobotController::getData(){
    _myRobot->readyRead();
    _sensorFL = distanceConversion(_myRobot->getSensorFL());
    _sensorFR = distanceConversion(_myRobot->getSensorFR());
    _sensorBL = distanceConversion(_myRobot->getSensorBL());
    _sensorBR = distanceConversion(_myRobot->getSensorBR());
}


QString RobotController::getCamStream(){
    QString streamAddr = "http://192.168.1.11:8080/?action=stream";
    return streamAddr;
}

int RobotController::getBattery() {     return _battery;    }
float RobotController::getSensorFL() {     return _sensorFL;    }
float RobotController::getSensorFR() {     return _sensorFR;    }
float RobotController::getSensorBL() {     return _sensorBL;    }
float RobotController::getSensorBR() {     return _sensorBR;    }

float distanceConversion(int sensorVal){
    if(sensorVal > 215)
        return -15/100;
    if(sensorVal < 31)
        return 150/100;

    // 255 distance values
    // We've take 5 cm as limit for change
    int distance[255] = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
                         0,0,0,0,0, 150,145,145,145,140, 140,140,140,135,135, 135,135,135,135,135, 130,125,125,120,115,
                         110,105,100,95,90, 90,90,85,85,85, 80,80,80,80,80, 75,75,75,75,75, 70,70,70,70,70,
                         70,70,70,65,65, 65,65,65,65,65, 60,60,60,60,60, 60,55,55,55,55, 55,55,50,50,50,

                         50,50,50,50,50, 50,45,45,45,45, 45,45,45,45,45, 45,45,40,40,40, 40,40,40,40,40,
                         40,40,40,40,40, 40,40,40,40,40, 40,40,40,40,40, 40,40,35,35,35, 35,35,35,35,35,
                         35,35,35,35,35, 35,35,35,30,30, 30,30,30,30,30, 30,30,30,30,30, 30,30,30,25,25,
                         25,25,25,25,25, 25,25,25,25,25, 25,25,25,20,20, 20,20,20,20,20, 20,20,20,20,20,

                         15,15,15,15,15, 15,15,15,15,15, 15,15,15,15,-15, 0,0,0,0,0, 0,0,0,0,0,
                         0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
                         0,0,0,0,0,
                        };

    return distance[sensorVal]/100;
}
