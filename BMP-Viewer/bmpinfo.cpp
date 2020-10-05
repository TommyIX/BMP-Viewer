#include "bmpinfo.h"
#include "ui_bmpinfo.h"
#include <QStringListModel>

bmpinfo::bmpinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bmpinfo)
{
    ui->setupUi(this);

}

bmpinfo::~bmpinfo()
{
    delete ui;
}

void bmpinfo::bmpinfoprint(std::string *strtodisplay){
    QStringList todisplaybmpinfo;
    int i=0;
    while(*(strtodisplay+i)!=""&&(strtodisplay+i)!=NULL){
        todisplaybmpinfo<<QString::fromStdString(*(strtodisplay+i));
        i++;
    }
    QStringListModel *model = new QStringListModel(todisplaybmpinfo);
    ui->listView->setModel(model);
}

void bmpinfo::plotinit(QImage *img){
    double yrange=0;
    int nWidth = img->width();
    int nHeight = img->height();
    QVector<double> vecX;
    QVector<double> vecY(256,0);
    for(int i=0;i<256;i++){vecX.append(i);}
    for(int j = 0; j < nHeight; j++){
        for(int k = 0; k < nWidth; k++){
            QColor pxlcolor;
            pxlcolor = img->pixelColor(k,j);
            int nIndex = int(pxlcolor.red()*0.3+pxlcolor.green()*0.59+pxlcolor.blue()*0.11);
            vecY[nIndex] = vecY.at(nIndex) + 1;
            if (vecY[nIndex]>yrange) yrange=vecY[nIndex];
        }
    }
    ui->widget->xAxis->setRange(0,256);
    ui->widget->yAxis->setRange(0,(int)yrange);
    double yMax = 0;
    for(int j = 0; j < 256 ; j++){
       if(yMax < vecY.at(j)){yMax = vecY.at(j);}
    }
    QCPBars *bars = new QCPBars(ui->widget->xAxis, ui->widget->yAxis);
    bars->setData(vecX, vecY);
    bars->setPen(QColor(0, 0, 0));
    bars->setWidth(0.05);
    ui->widget->setVisible(true);
    ui->widget->replot();
}
