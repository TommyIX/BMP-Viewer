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
    QString fileName = QFileDialog::getSaveFileName(this,tr("保存到指定位置"),"",tr("Text File (*.txt)"));
    if (!fileName.isNull())
        {
            std::ofstream out(fileName.toStdString());
            out<<"#格式：(x,y)[R,G,B]\n";
            for(int i=0;i<imagesource.height();i++){
                for(int j=0;j<imagesource.width();j++){
                    QColor pixelcolorhere = imagesource.pixelColor(i,j);
                    out<<"("<<j<<","<<i<<"),["<<pixelcolorhere.red()<<","<<pixelcolorhere.green() << "," <<pixelcolorhere.blue()<<"]\n";
                }
            }
            out.close();
            QMessageBox::information(NULL, "成功", "像素信息文件成功保存");
        }
}
void BMPDisplay::on_action_2_triggered()
{
    QMessageBox::about(NULL,"关于本软件","图像处理作业 2020\n 王锦宏 19351125");
}

void BMPDisplay::on_action_3_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("保存到指定位置"),"",tr("Bitmap Image (*.bmp)"));
            if (!fileName.isNull())
            {
                imagesource.save(fileName);
                QMessageBox::information(NULL, "成功", "BMP文件成功保存");
            }
}
