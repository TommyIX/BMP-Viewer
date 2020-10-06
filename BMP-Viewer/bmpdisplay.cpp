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
    QPen pen;
    QPixmap tempPixmap = QPixmap::fromImage(imagesource);
    painter.drawPixmap(0,0,tempPixmap);
    return;
}

void BMPDisplay::importpaintimage(QImage& source){
    imagesource=source;
}

void BMPDisplay::on_action_4_triggered()
{

}
