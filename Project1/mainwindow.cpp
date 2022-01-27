#include "mainwindow.h"
#include "onedollar.cpp"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include "onedollar.h"


MainWindow::MainWindow(QWidget *parent) :
    //Uses UI file to create a canvas quickly for easy of use
    QMainWindow(parent),
    ui( new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setFixedSize(QSize(900,600));

}

MainWindow::~MainWindow()
{
    delete ui;
}
//Bad practice
int xPoint = -1;
int yPoint = -1;

void MainWindow::paintEvent(QPaintEvent *)
{

    //Main window Updater
    QPainter painter(this);
    QPen pen(Qt::blue,20,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    painter.setPen(pen);
    if(xPoint >0){
    painter.drawPoint(xPoint,yPoint);
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){

    xPoint = event->pos().x();
    yPoint = event->pos().y();
    //Allows the drawing to not be deleted on update
   update(xPoint,yPoint,6,6);
    }
    if(event->button()== Qt::RightButton)
    {
        //Uses the behavior of update to act as mass delete on right click
        xPoint = -1;
        update();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton){

    xPoint = event->pos().x();
    yPoint = event->pos().y();
    update(xPoint,yPoint,6,6);
    }
}

