#include "drawingwindow.h"
#include "ui_drawingwindow.h"

DrawingWindow::DrawingWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DrawingWindow)
{
    ui->setupUi(this);
}

DrawingWindow::~DrawingWindow()
{
    delete ui;
}

