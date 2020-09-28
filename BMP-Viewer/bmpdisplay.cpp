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

