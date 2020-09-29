#include "bmpdisplay.h"
#include "ui_bmpdisplay.h"


BMPDisplay::BMPDisplay(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BMPDisplay)
{
    ui->setupUi(this);
}

BMPDisplay::~BMPDisplay()
{
    delete ui;
}

void BMPDisplay::paintEvent(QPaintEvent *) {
    QPainter painter(this); // this 是 PaintTest 的指针
    painter.setPen(Qt::gray);
    painter.setBrush(Qt::green);
    painter.drawRect(10, 10, 50, 50);
}
