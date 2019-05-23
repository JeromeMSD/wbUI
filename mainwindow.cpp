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

    // --- Set interactive component ---
    // Slider
    ui->speedSlider->setMinimum(0);
    ui->speedSlider->setMaximum(100);

    // Connect Button Connection to appropriate slot
    connect(ui->connectionButton,SIGNAL(clicked()),SLOT(startConnection()));
    connect(ui->speedSlider,SIGNAL(valueChanged(int)),SLOT(handleSlider()));


}

void MainWindow::startConnection(){
    ui->console->append("Tentative de connection...");
    ui->connectionButton->setText("Disconnection");

    // --- MYROBOT CALL ---
    ui->cam->setStyleSheet("background-image:url(background_app.png);");
}

void MainWindow::handleSlider(){
    ui->console->append("coucou");
    ui->speedValue->display(ui->speedSlider->value());
}
