#ifndef BMPDISPLAY_H
#define BMPDISPLAY_H

#include <QMainWindow>
#include <fstream>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
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
    ~BMPDisplay();
    void paintEvent(QPaintEvent *);
    void importpaintimage(QImage&);

private slots:
    void on_action_4_triggered();

    void on_action_triggered();

    void on_action_2_triggered();

private:
    Ui::BMPDisplay *ui;
    QImage imagesource;
};
#endif // BMPDISPLAY_H
