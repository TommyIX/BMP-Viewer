#include "dialog.h"
#include <math.h>
#include <string>
#include <QApplication>
#include <QException>
#include <QMenuBar>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <windows.h>
using std::string;

//函数定义表
void BMPRead(string);
void CharReverse(unsigned char*, int);
long long HexChartoint(unsigned char*, int);
void byteflowreadint(std::ifstream*,int,int*);
void PaintBMP(Dialog*);

//常量表
const char hex[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

struct BMPfilehead{ //第一部分数据：BMP文件头
    bool successfullyopened=false;
    long long sizebyte;//文件大小变量
    long long shiftbyte;//偏移量
}Targethead;
struct BMPinformation{ //第二部分数据：位图信息
    int width=100;
    int height=100;
    int pixelbit;
    int compassrate; //8位，若为0则不压缩
    int size;
    int horizontalresolution; //水平分辨率
    int verticalresolution; //垂直分辨率
    int acturalcolorindex;
    int importantcolorindex;
}Targetinfo;
struct RGBA{
    int R,G,B,A;
};
RGBA* ColorTable;
RGBA* ColorData;

int main(int argc, char *argv[]){ //QT窗口生成
    QApplication a(argc, argv);
    Dialog w;
    BMPRead("C:\\Users\\jhong\\Desktop\\bmp.bmp");
    if(Targethead.successfullyopened) w.setFixedSize(Targetinfo.width,Targetinfo.height);

    w.show();
    return a.exec();
}

void PaintBMP(Dialog* wpnt){
    for(int i=0;i<Targetinfo.height;i++){

    }
}

void BMPRead(string source){ //BMP解码器
    unsigned char* thishead;
    std::ifstream bmpin(source,std::ios::in|std::ios::binary);
    if (!bmpin) {qDebug("File can not be opened");return;}

    //文件头读取与检查部分
    thishead = new unsigned char[2]; //读入前两位判断是否为BMP文件头
    for(int i=0;i<2;i++){
        bmpin>>*(thishead+i);
    }
    if (*thishead!='B'||*(thishead+1)!='M') {qDebug("Not a BMP file!");return;}
    delete thishead;

    thishead = new unsigned char[4]; //读入文件大小
    for(int i=0;i<4;i++){
        bmpin>>*(thishead+i);
    }
    CharReverse(thishead,4);
    Targethead.sizebyte=HexChartoint(thishead,4);
    delete thishead;

    thishead = new unsigned char[4]; //检查保留段完整性
    for(int i=0;i<4;i++){
        bmpin>>*(thishead+i);
        if (*(thishead+i)!=0) {qDebug("Reserve part ERROR");return;}
    }
    delete thishead;

    thishead = new unsigned char[4]; //读入偏移距离
    for(int i=0;i<4;i++){
        bmpin>>*(thishead+i);
    }
    CharReverse(thishead,4);
    Targethead.shiftbyte=HexChartoint(thishead,4);
    delete thishead;

    thishead = new unsigned char[4]; //检查位图信息头大小是否为40
    for(int i=0;i<4;i++){
        bmpin>>*(thishead+i);
    }
    CharReverse(thishead,4);
    if(HexChartoint(thishead,4)!=40) {qDebug("Only Support BMP File with V3 header");return;}
    delete thishead;
/*
    thishead = new unsigned char[4]; //读入width
    for(int i=0;i<4;i++){
        bmpin>>*(thishead+i);
    }
    CharReverse(thishead,4);
    Targetinfo.width=HexChartoint(thishead,4);
    delete thishead;

    thishead = new unsigned char[4]; //读入height
    for(int i=0;i<4;i++){
        bmpin>>*(thishead+i);
    }
    CharReverse(thishead,4);
    Targetinfo.height=HexChartoint(thishead,4);
    delete thishead;

    thishead = new unsigned char[2]; //去掉固定的0x0001
    for(int i=0;i<2;i++){
        bmpin>>*(thishead+i);
    }
    delete thishead;

    thishead = new unsigned char[2]; //读入像素所占颜色数
    for(int i=0;i<2;i++){
        bmpin>>*(thishead+i);
    }
    CharReverse(thishead,2);
    Targetinfo.pixelbit=HexChartoint(thishead,2);
    delete thishead;

    thishead = new unsigned char[4]; //读入压缩率
    for(int i=0;i<4;i++){
        bmpin>>*(thishead+i);
    }
    CharReverse(thishead,4);
    Targetinfo.compassrate=HexChartoint(thishead,4);
    delete thishead;

    thishead = new unsigned char[4]; //读入图像的大小(BI_RGB下为0)
    for(int i=0;i<4;i++){
        bmpin>>*(thishead+i);
    }
    CharReverse(thishead,4);
    Targetinfo.size=HexChartoint(thishead,4);
    delete thishead;

    thishead = new unsigned char[4]; //读入水平分辨率
    for(int i=0;i<4;i++){
        bmpin>>*(thishead+i);
    }
    CharReverse(thishead,4);
    Targetinfo.horizontalresolution=HexChartoint(thishead,4);
    delete thishead;

    thishead = new unsigned char[4]; //读入垂直分辨率
    for(int i=0;i<4;i++){
        bmpin>>*(thishead+i);
    }
    CharReverse(thishead,4);
    Targetinfo.verticalresolution=HexChartoint(thishead,4);
    delete thishead;

    thishead = new unsigned char[4]; //读入实际颜色
    for(int i=0;i<4;i++){
        bmpin>>*(thishead+i);
    }
    CharReverse(thishead,4);
    Targetinfo.acturalcolorindex=HexChartoint(thishead,4);
    delete thishead;

    thishead = new unsigned char[4]; //读入关键颜色
    for(int i=0;i<4;i++){
        bmpin>>*(thishead+i);
    }
    CharReverse(thishead,4);
    Targetinfo.importantcolorindex=HexChartoint(thishead,4);
    delete thishead;*/

    //BMP文件信息读取部分
    byteflowreadint(&bmpin,4,&Targetinfo.width); //读入宽度
    byteflowreadint(&bmpin,4,&Targetinfo.height);//读入高度
    byteflowreadint(&bmpin,2,NULL);//抛弃为1的值
    byteflowreadint(&bmpin,2,&Targetinfo.pixelbit);//读入像素所占比特数
    byteflowreadint(&bmpin,4,&Targetinfo.compassrate);//读入压缩率，0为BI_RGB
    byteflowreadint(&bmpin,4,&Targetinfo.size);//读入图像大小
    byteflowreadint(&bmpin,4,&Targetinfo.horizontalresolution);//读入水平分辨率
    byteflowreadint(&bmpin,4,&Targetinfo.verticalresolution);//读入垂直分辨率
    byteflowreadint(&bmpin,4,&Targetinfo.acturalcolorindex);//读入实际颜色索引数
    byteflowreadint(&bmpin,4,&Targetinfo.importantcolorindex);//读入重要颜色索引数

    //BMP颜色表读取部分
    ColorTable = (RGBA*)malloc(Targetinfo.acturalcolorindex * sizeof(RGBA));
    unsigned char temp;
    for (int i = 0; i < Targetinfo.acturalcolorindex; i++) {
        bmpin >> temp;
        (ColorTable + i)->B = int(temp);
        bmpin >> temp;
        (ColorTable + i)->G = int(temp);
        bmpin >> temp;
        (ColorTable + i)->R = int(temp);
        bmpin >> temp;
        (ColorTable + i)->A = int(temp);
     }
     long long allpixels = Targetinfo.width * Targetinfo.height / 3;
     ColorData = (RGBA*)malloc(allpixels * sizeof(RGBA));
     for (int i = 0; i < allpixels; i++) {
        bmpin >> temp;
        (ColorData + i)->B = int(temp);
        bmpin >> temp;
        (ColorData + i)->G = int(temp);
        bmpin >> temp;
        (ColorData + i)->R = int(temp);
     }
     Targethead.successfullyopened=true;
}
void byteflowreadint(std::ifstream* source,int length,int* savelocation){
    unsigned char* temp = (unsigned char*)malloc(length*sizeof(unsigned char));
    for(int i=0;i<length;i++){
        *source>>*(temp+i);
    }
    CharReverse(temp,length);
    if(savelocation!=NULL)*savelocation=HexChartoint(temp,length);
    free(temp);
}
void CharReverse(unsigned char* target, int length) { //对于常见的反向读取的binary，需要先使用这个命令来reverse
    unsigned char temp;
    for (int i = 0; i < length / 2; i++) {
        temp = *(target + i);
        *(target + i) = *(target + length - i - 1);
        *(target + length - i - 1) = temp;
    }
    return;
}
long long HexChartoint(unsigned char* target, int length) { //注意：为HexChar正向计算，对于BMP文件的大小等等，需要先reverse
    string toconverthex = "";
    int temptarget, decnum[2];
    for (int i = 0; i < length; i++) {
        temptarget = *(target + i);
        decnum[0] = temptarget / 16;
        decnum[1] = temptarget % 16;
        toconverthex = toconverthex + hex[decnum[0]] + hex[decnum[1]];
    }
    int powwhat = length * 2 - 1;
    long long output = 0;
    for (int i = 0; i < 2 * length; i++) {
        if (toconverthex[i] >= 'A' && toconverthex[i] <= 'F') {
            output += (int(toconverthex[i]) - int('A') + 10) * pow(16, powwhat);
        }
        else {
            output += (int(toconverthex[i]) - int('0')) * pow(16, powwhat);
        }
        powwhat--;
    }
    return output;
}
//next
