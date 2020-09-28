#ifndef BMPDISPLAY_H
#define BMPDISPLAY_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class BMPDisplay; }
QT_END_NAMESPACE

class BMPDisplay : public QMainWindow
{
    Q_OBJECT

public:
    BMPDisplay(QWidget *parent = nullptr);
    ~BMPDisplay();

private:
    Ui::BMPDisplay *ui;
};
#endif // BMPDISPLAY_H
