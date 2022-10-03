#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QSerialPort>
#include<QDebug>

QSerialPort *serial;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial =new QSerialPort(this);

    //define in ctor serial config
    serial->setPortName("com4");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    serial->open(QIODevice::ReadWrite);
    serial->write("ok");

    connect(serial , SIGNAL(readyRead()) , this , SLOT(serialReceived()));

}

MainWindow::~MainWindow()
{
    delete ui;
    serial->close();

}

void MainWindow::serialReceived()
{
    QByteArray barr;
    barr=serial->readAll();

    ui->label->setText(barr);
    qDebug()<<barr;
}


