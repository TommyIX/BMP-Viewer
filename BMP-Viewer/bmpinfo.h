#ifndef BMPINFO_H
#define BMPINFO_H

#include <string>
#include <QDialog>
#include <qcustomplot.h>

namespace Ui {
class bmpinfo;
}

class bmpinfo : public QDialog
{
    Q_OBJECT

public:
    explicit bmpinfo(QWidget *parent = nullptr);
    ~bmpinfo();
    void bmpinfoprint(std::string*);
    void plotinit(QImage*);
private:
    Ui::bmpinfo *ui;
};

#endif // BMPINFO_H
