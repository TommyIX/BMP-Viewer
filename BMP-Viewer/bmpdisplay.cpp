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
    painter.drawRect(100, 100, 50, 50);
    return;
}


/*void BMPDisplay::paintpixel(int r, int g, int b, int a, int x, int y){
    painter.
    thiscolor.setRed(r);
    thiscolor.setGreen(g);
    thiscolor.setBlue(b);
    thiscolor.setAlpha(a);
    painter.drawPoint(x,y);
}
*/
