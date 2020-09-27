#include "dialog.h"
#include <math.h>
#include <string>
#include <QApplication>
#include <QException>
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

//常量表
const char hex[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

struct BMPfilehead{ //第一部分数据：BMP文件头
    long long sizebyte;//文件大小变量
    long long shiftbyte;//偏移量
}Targethead;
struct BMPinformation{ //第二部分数据：位图信息
    int width;
    int height;
}Targetinfo;

int main(int argc, char *argv[]){ //QT窗口生成
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}

void BMPRead(string source){ //BMP解码器
    unsigned char* thishead;
    std::ifstream bmpin(source,std::ios::in|std::ios::binary);
    if (!bmpin) {qDebug("File can not be opened");return;}

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

    //进一步操作一波
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
