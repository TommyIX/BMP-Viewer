#include "bmpinfo.h"
#include "ui_bmpinfo.h"
#include <QStringListModel>
using std::string;

struct BMPFilehead{
    bool successfullyopened=false;
    long long sizebyte;//文件大小变量
    long long shiftbyte;//偏移量
};
extern BMPFilehead Targethead;
struct BMPinformation{
    int width=100;
    int height=100;
    int pixelbit;
    int compassrate; //8位，若为0则不压缩
    int size;
    int horizontalresolution; //水平分辨率
    int verticalresolution; //垂直分辨率
    int acturalcolorindex;
    int importantcolorindex;
};
extern BMPinformation Targetinfo;


bmpinfo::bmpinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bmpinfo)
{
    ui->setupUi(this);
    QStringList todisplaybmpinfo;
    todisplaybmpinfo<<QString::fromStdString("文件大小："+numtostr(Targethead.sizebyte)+"Bytes");
    todisplaybmpinfo<<QString::fromStdString("文件偏移量："+numtostr(Targethead.shiftbyte)+"Bytes");
    todisplaybmpinfo<<QString::fromStdString("图像宽度："+numtostr(Targetinfo.width)+"Pixels");
    todisplaybmpinfo<<QString::fromStdString("图像高度："+numtostr(Targetinfo.height)+"Pixels");
    todisplaybmpinfo<<QString::fromStdString("图像位宽："+numtostr(Targetinfo.pixelbit));
    todisplaybmpinfo<<QString::fromStdString("图像压缩率："+numtostr(Targetinfo.compassrate));
    todisplaybmpinfo<<QString::fromStdString("图像bi_size："+numtostr(Targetinfo.size));
    todisplaybmpinfo<<QString::fromStdString("图像水平分辨率："+numtostr(Targetinfo.horizontalresolution)+"Pixels/metre");
    todisplaybmpinfo<<QString::fromStdString("图像垂直分辨率："+numtostr(Targetinfo.verticalresolution)+"Pixels/metre");
    todisplaybmpinfo<<QString::fromStdString("图像实际颜色索引："+numtostr(Targetinfo.acturalcolorindex));
    todisplaybmpinfo<<QString::fromStdString("图像重要颜色索引："+numtostr(Targetinfo.importantcolorindex));
    QStringListModel *model = new QStringListModel(todisplaybmpinfo);
    ui->listView->setModel(model);
}

bmpinfo::~bmpinfo()
{
    delete ui;
}

