#ifndef BMPINFO_H
#define BMPINFO_H

#include <string>
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
    void bmpinfoprint(std::string*);

private:
    Ui::bmpinfo *ui;
};

#endif // BMPINFO_H
