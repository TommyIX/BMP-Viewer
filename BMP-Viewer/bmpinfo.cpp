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
