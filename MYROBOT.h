#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>

class MyRobot : public QObject {
    Q_OBJECT
public:
    MyRobot(QObject *parent = 0);
    void doConnect();
    void disConnect();
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;

signals:
    void updateUI(const QByteArray Data);
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();
    void speed(char speed_right, char speed_left, bool dir_right, bool dir_left);
    QByteArray getDataReceive();
    qint16 crc16(QByteArray adresse_tab , unsigned char max_lenght);
    int getBat();
    int getSensorFL();
    int getSensorFR();
    int getSensorBL();
    int getSensorBR();
    float getOdo();
    int getSpeedWR();
    int getSpeedWL();

private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;
};

#endif // MYROBOT_H
