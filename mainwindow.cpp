#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MYROBOT.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    ui->state->setText("Disconnected");
    // --- Date Set ---
    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (buffer,80,"%d - %m - %y",timeinfo);

    ui->date->setText(buffer);
    setBatteryBar(100);
    ui->progressBar->setValue(0);

    // --- Set interactive component ---
    // Slider
    ui->speedSlider->setMinimum(0);
    ui->speedSlider->setMaximum(100);

    // Connect Button Connection to appropriate slot
    connect(ui->connectionButton,SIGNAL(clicked()),SLOT(startConnection()));
    connect(ui->speedSlider,SIGNAL(valueChanged(int)),SLOT(handleSlider()));

    // Default speed
    //ui->speedSlider->setValue(50);
    // --- Init WifiBotObject ---
    wifiBot = new MyRobot();
    rbController = new RobotController(wifiBot);

}

void MainWindow::startConnection(){

    if(ui->connectionButton->text() == "Connection"){
        ui->console->append("Try to connect...");
        ui->connectionButton->setText("Disconnection");

        // --- MYROBOT CALL ---
        wifiBot->doConnect();

        //load(QUrl("http://192.168.1.106:8080/?action=stream"));
    }else {
        ui->console->append("Disconnection...");
        ui->connectionButton->setText("Connection");

        // --- MYROBOT CALL ---
        wifiBot->disConnect();
    }

}


void MainWindow::go(int way){
    switch(way){
        case 1:
            qDebug() << "go front";
            rbController->goFront();
            setBatteryBar(15);
            break;
        case 2:
            qDebug() << "go back";
            rbController->goBack();
            break;
        case 3:
            qDebug() << "go left";
            rbController->turnLeft(false);
            break;
        case 4:
            qDebug() << "go right";
            rbController->turnRight(false);
            break;
        case 5:
            qDebug() << "go front left";
            rbController->turnLeft(true);
            break;
        case 6:
            qDebug() << "go front right";
            rbController->turnRight(true);
            break;
        default:
           qDebug() << "Error - Switch - go() - Not suppose to be here... ";
           rbController->stop();
    }

}

void MainWindow::handleSlider(){
    // Set new Speed Value
    rbController->setSpeed((ui->speedSlider->value()*240)/100);

    ui->speedValue->display(ui->speedSlider->value());
    ui->progressBar->setValue(ui->speedSlider->value());
}

void MainWindow::setBatteryBar(int value){
    ui->batteryBar->setValue(value);
    if(value < 20)
           ui->batteryBar->setStyleSheet("QProgressBar{\
                                         color:#eee;\
                                         }\
                                         QProgressBar:horizontal {\
                                         border:#2c2c2c;\
                                         padding-right: 30px;\
                                         text-align : right;\
                                         }\
                                         QProgressBar::chunk:horizontal {\
                                         background: qlineargradient(x1: -0.5, y1: 0.5, x2: 1, y2: 0.5, stop: 1 #EE0000, stop: 0 #2c2c2c);\
                                         }");
}

/// --- Direction Button ---
void MainWindow::on_front_pressed(){    go(1);  }
void MainWindow::on_back_pressed(){    go(2);  }
void MainWindow::on_left_pressed(){    go(3);  }
void MainWindow::on_right_pressed(){    go(4);  }
void MainWindow::on_frontLeft_pressed(){    go(5);  }
void MainWindow::on_frontRight_pressed(){    go(6);  }

void MainWindow::on_front_released(){   rbController->stop();  }
void MainWindow::on_left_released(){    rbController->stop();  }
void MainWindow::on_back_released(){    rbController->stop();  }
void MainWindow::on_right_released(){    rbController->stop();  }
void MainWindow::on_frontLeft_released(){  rbController->stop();  }
void MainWindow::on_frontRight_released(){   rbController->stop();  }
