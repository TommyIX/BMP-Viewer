#ifndef BMPDISPLAY_H
#define BMPDISPLAY_H

#include <QMainWindow>
#include <QPainter>
#include <QWidget>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui { class BMPDisplay; }
QT_END_NAMESPACE

class BMPDisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit BMPDisplay(QWidget *parent = 0);
    //BMPDisplay(QWidget *parent = nullptr);
    ~BMPDisplay();
    void paintEvent(QPaintEvent *);
    void paintpixel(int,int,int,int,int,int);

private:
    Ui::BMPDisplay *ui;
};
#endif // BMPDISPLAY_H
