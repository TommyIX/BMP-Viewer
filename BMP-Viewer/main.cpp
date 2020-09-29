#include "bmpdisplay.h"
#include "bmpinfo.h"
#include "main.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BMPDisplay w;
    bmpinfo inf;
    BMPRead("C:\\Users\\JHong\\Desktop\\testbmp\\default\\bmp.bmp");
    w.setFixedSize(QSize(Targetinfo.width,Targetinfo.height));
    /*
    if(Targethead.successfullyopened){
        for(int j=Targetinfo.height;j>=0;j--){
            for(int i=1;i<=Targetinfo.width;i++){
                RGBA temp = *(ColorData+(j-1)*Targetinfo.width+i);
                w.paintwith(temp.R,temp.G,temp.B,0,i,j);
            }
        }
    }
    */
    w.show();
    if(Targethead.successfullyopened){
        string wtw[12];
        wtw[0]="文件大小："+numtostr(Targethead.sizebyte)+"Bytes";
        wtw[1]="文件偏移量："+numtostr(Targethead.shiftbyte)+"Bytes";
        wtw[2]="图像宽度："+numtostr(Targetinfo.width)+"Pixels";
        wtw[3]="图像高度："+numtostr(Targetinfo.height)+"Pixels";
        wtw[4]="图像位宽："+numtostr(Targetinfo.pixelbit);
        wtw[5]="图像压缩率："+numtostr(Targetinfo.compassrate);
        wtw[6]="图像bi_size："+numtostr(Targetinfo.size);
        wtw[7]="图像水平分辨率："+numtostr(Targetinfo.horizontalresolution)+"Pixels/metre";
        wtw[8]="图像垂直分辨率："+numtostr(Targetinfo.verticalresolution)+"Pixels/metre";
        wtw[9]="图像实际颜色索引："+numtostr(Targetinfo.acturalcolorindex);
        wtw[10]="图像重要颜色索引："+numtostr(Targetinfo.importantcolorindex);
        inf.bmpinfoprint(wtw);
    }
    inf.show();
    return a.exec();
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

    //BMP文件信息读取部分
    byteflowreadint(&bmpin,4,&Targetinfo.width); //读入宽度
    byteflowreadint(&bmpin,4,&Targetinfo.height);//读入高度
    byteflowreadint(&bmpin,2,NULL);//抛弃为1的值
    byteflowreadint(&bmpin,2,&Targetinfo.pixelbit);//读入像素所占比特数
    byteflowreadint(&bmpin,4,&Targetinfo.compassrate);//读入压缩率，0为BI_RGB
    byteflowreadint(&bmpin,4,&Targetinfo.size);//读入图像大小
    byteflowreadint(&bmpin,2,&Targetinfo.horizontalresolution);//读入水平分辨率
    byteflowreadint(&bmpin,2,NULL);//抛弃为1的值
    byteflowreadint(&bmpin,2,&Targetinfo.verticalresolution);//读入垂直分辨率
    byteflowreadint(&bmpin,2,NULL);//抛弃为1的值
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
