#ifndef DRAWINGWINDOW_H
#define DRAWINGWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class DrawingWindow; }
QT_END_NAMESPACE

class DrawingWindow : public QMainWindow
{
    Q_OBJECT

public:
    DrawingWindow(QWidget *parent = nullptr);
    ~DrawingWindow();

private:
    Ui::DrawingWindow *ui;
};
#endif // DRAWINGWINDOW_H
