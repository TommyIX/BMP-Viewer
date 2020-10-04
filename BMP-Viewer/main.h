#ifndef MAIN_H
#define MAIN_H

#include <QApplication>
#include <QException>
#include <QMenuBar>
#include <math.h>
#include <string>
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
// *RTable,*GTable,*BTable,*ATable;
//int *RData,*GData,*BData,*AData;
int* allimdata;

/*struct RGBA{
    int R,G,B,A=255;
};
RGBA* ColorTable;
RGBA* ColorData;*/

template <class M>
string numtostr(M numtop){
    std::stringstream ss;
    ss<<numtop;
    return ss.str();
}
#endif
