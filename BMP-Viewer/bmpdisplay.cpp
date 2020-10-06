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
    if(!imagesource.isNull()){
    QPixmap tempPixmap = QPixmap::fromImage(imagesource);
    painter.drawPixmap(0,0,tempPixmap);}
    return;
}

void BMPDisplay::importpaintimage(QImage& source){
    imagesource=source;
}

void BMPDisplay::on_action_4_triggered()
{
    exit(0);
}

void BMPDisplay::on_action_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("保存到指定位置"),"",tr("Bitmap Image (*.bmp)"));
        if (!fileName.isNull())
        {
            imagesource.save(fileName);
            QMessageBox::information(NULL, "成功", "文件成功保存了");
        }
}
void BMPDisplay::on_action_2_triggered()
{
    QMessageBox::information(NULL,"关于本软件","图像处理作业 2020\n 王锦宏 19351125");
}
