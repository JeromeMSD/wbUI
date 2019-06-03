// myrobot.cpp

#include "MYROBOT.h"

MyRobot::MyRobot(QObject *parent) : QObject(parent) {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0;
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x0;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer
}


void MyRobot::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);
    socket->connectToHost("192.168.1.106", 15020); // connection to wifibot
    // we need to wait...
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        return;
    }
    TimerEnvoi->start(75);

}

void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

void MyRobot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
}

void MyRobot::disconnected() {
    qDebug() << "disconnected...";
}

void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void MyRobot::readyRead() {
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    emit updateUI(DataReceived);
    qDebug() << DataReceived[0] << DataReceived[1] << DataReceived[2];
}

void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}

void MyRobot::speed(char speed_right, char speed_left, bool dir_right, bool dir_left){
        DataToSend[2] = speed_left;
        DataToSend[3] = 0;
        DataToSend[4] = speed_right;
        DataToSend[5] = 0;
        DataToSend[6] = (0b0000000 | (dir_left << 6) | (dir_right << 4));
        qint16 crc = crc16(DataToSend,7);
        DataToSend[7] = (qint8)(crc);
        DataToSend[8] = (qint8)(crc >> 8);
}


qint16 MyRobot::getDataReceive(){
    return data_tab;
}

qint16 MyRobot::crc16(QByteArray adresse_tab ,unsigned char max_lenght){
        unsigned int crc = 0xFFFF;
        unsigned int poly = 0xA001;
        unsigned int parity= 0;

        for (unsigned int cptO= 1 ; cptO < max_lenght ; cptO++){
                crc ^= (unsigned char)(adresse_tab[cptO]);
                for (unsigned int cptB = 0; cptB <= 7 ; cptB++){
                        parity= crc;
                        crc >>= 1;
                        if (parity%2 == 1) crc ^= poly;
                }
        }

        return(crc);
}
