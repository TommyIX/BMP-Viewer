#ifndef BMPINFO_H
#define BMPINFO_H

#include <QDialog>

namespace Ui {
class bmpinfo;
}

class bmpinfo : public QDialog
{
    Q_OBJECT

public:
    explicit bmpinfo(QWidget *parent = nullptr);
    ~bmpinfo();

private:
    Ui::bmpinfo *ui;
};

#endif // BMPINFO_H
