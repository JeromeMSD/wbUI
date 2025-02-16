#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MYROBOT.h"

//#include <QWebEngineView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete rbController;
    delete ui;
}

void MainWindow::init(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    this->changeState(1);
    // --- Date Set ---
    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (buffer,80,"%d - %m - %y",timeinfo);

    // --- Set UI elements ---
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

    // --- Init wifiBot Controler ---
    rbController = new RobotController();

    // Default speed
    ui->speedSlider->setValue(75);
}

void MainWindow::startConnection(){
    if(ui->connectionButton->text() == "Connection"){
        ui->console->append("Try to connect...");

        rbController->startConnection();

        ui->console->append(" ### wifiBot Connected ### ");
        ui->connectionButton->setText("Disconnection");
        this->changeState(0);

        // Try to get webcam video stream
        ui->console->append("research of video stream from");

        ui->web->load(QUrl(rbController->getCamStream()));
        ui->web->show();


        ui->console->append(" ### wifiBot Connected ### ");

    }else {
        ui->console->append("Disconnection...");
        ui->connectionButton->setText("Connection");
        this->changeState(1);

        rbController->endConnection();
        ui->console->append(" ### wifiBot Disconnected ### ");
    }

}

// Set a new Speed Value for UI and for the wifiBot
void MainWindow::handleSlider(){
    rbController->setSpeed((ui->speedSlider->value()*240)/100);

    ui->speedValue->display(ui->speedSlider->value());
    ui->progressBar->setValue(ui->speedSlider->value());
    ui->centralWidget->setFocus();
}



/*
 * -----------------------
 *    Moving function
 * -----------------------
 */
void MainWindow::go(int way){
    switch(way){
        case 1:
            qDebug() << "go front";
            rbController->goFront();
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

        default:
           qDebug() << "Error - Switch - go() - Not suppose to be here... ";
           rbController->stop();
    }
}

/// --- Direction Button ---
void MainWindow::on_front_pressed(){    go(1);  }
void MainWindow::on_back_pressed(){    go(2);  }
void MainWindow::on_left_pressed(){    go(3);  }
void MainWindow::on_right_pressed(){    go(4);  }

void MainWindow::on_front_released(){   rbController->stop(); ui->centralWidget->setFocus(); }
void MainWindow::on_left_released(){    rbController->stop(); ui->centralWidget->setFocus(); }
void MainWindow::on_back_released(){    rbController->stop(); ui->centralWidget->setFocus(); }
void MainWindow::on_right_released(){    rbController->stop(); ui->centralWidget->setFocus(); }

/// --- Direction keyboard ---
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Up:
            go(1);
            break;
        case Qt::Key_Down:
            go(2);
            break;
        case Qt::Key_Left:
            go(3);
            break;
        case Qt::Key_Right:
            go(4);
            break;
        default:
            rbController->stop();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up || event->key() == Qt::Key_Down || event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
        rbController->stop();

    // Refresh after release. Going to be change to thread
    this->refreshUI();
}


/*
 * ------------------
 *    UI function
 * ------------------
 */

// Set battery with value place in parameter and set color to red if value inferieur.
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

// Change the top-left state text
void MainWindow::changeState(int state){
    switch (state) {
        case 0:
            ui->state->setText("Connected to wifiBot");
            ui->state->setStyleSheet("color:#00EE00;");
            break;
        case 1:
            ui->state->setText("Disconnected");
            ui->state->setStyleSheet("color:#ccc;");
            break;
        case 2:
            ui->state->setText("Error - WifiBot Error");
            ui->state->setStyleSheet("color:#EE0000;");
            break;
        default:
            ui->state->setText("Error - State Error");
            ui->state->setStyleSheet("color:#EEEE00;");
    }
}

// Refresh UI and Console informations
void MainWindow::refreshUI(){
    rbController->getData();

    // -- Console display --
    ui->console->append("--- Sensors ---");
    ui->console->append("Niveau de Batterie :" + QString::number(rbController->getBattery()));
    ui->console->append("Prox. detector Front-Left :" + QString::number(rbController->getSensorFL()));
    ui->console->append("Prox. detector Front-Right :" + QString::number(rbController->getSensorFR()));
    ui->console->append("Prox. detector Back-Left :" + QString::number(rbController->getSensorBL()));
    ui->console->append("Prox. detector Back-Right :" + QString::number(rbController->getSensorBR()));

    // -- UI display --
    setBatteryBar(rbController->getBattery());

    // Front Left Sensor
    if(rbController->getSensorFL() < 0.0)
        ui->flProx->setText("< "+QString::number(rbController->getSensorFL()) +" m");
    else if(rbController->getSensorFL() >= 1.5)
        ui->flProx->setText(">= "+QString::number(rbController->getSensorFL()) +" m");
    else
        ui->flProx->setText(QString::number(rbController->getSensorFL()) +" m");

    // Front Right Sensor
    if(rbController->getSensorFR() < 0.0)
        ui->frProx->setText("< "+QString::number(rbController->getSensorFR()) +" m");
    else if(rbController->getSensorFR() < 1.5)
        ui->frProx->setText(">= "+QString::number(rbController->getSensorFR()) +" m");
    else
        ui->frProx->setText(QString::number(rbController->getSensorFR()) +" m");

    // Back Left Sensor
    if(rbController->getSensorBL() < 0.0)
        ui->blProx->setText("< "+QString::number(rbController->getSensorBL()) +" m");
    else if(rbController->getSensorBL() < 1.5)
        ui->blProx->setText(">= "+QString::number(rbController->getSensorBL()) +" m");
    else
        ui->blProx->setText(QString::number(rbController->getSensorBL()) +" m");

    // Back Right Sensor
    if(rbController->getSensorBR() < 0.0)
        ui->brProx->setText("< "+QString::number(rbController->getSensorBR()) +" m");
    else if(rbController->getSensorBR() < 1.5)
        ui->brProx->setText(">= "+QString::number(rbController->getSensorBR()) +" m");
    else
        ui->brProx->setText(QString::number(rbController->getSensorBR()) +" m");
}
