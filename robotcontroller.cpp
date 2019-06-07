#include "robotcontroller.h"

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
    QByteArray data = _myRobot->getDataReceive();
    _battery =(unsigned char) (data[2] >> 2);
    qDebug() << _battery;
}

QString RobotController::getCamStream(){
    QString streamAddr = "http://192.168.1.106:8080/?action=stream";
    return streamAddr;
}

int RobotController::getBattery() {     return _battery;    }
int RobotController::getSensorFL() {     return _sensorFL;    }
int RobotController::getSensorFR() {     return _sensorFR;    }
int RobotController::getSensorBL() {     return _sensorBL;    }
int RobotController::getSensorBR() {     return _sensorBR;    }
