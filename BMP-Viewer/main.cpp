#include "main.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    string category;
    QString file_name = QFileDialog::getOpenFileName(NULL,QString::fromStdString("请打开一个BMP文件"),QString::fromStdString(""),QString::fromStdString("Bitmap Image (*.bmp)"),NULL,NULL);
        if (!file_name.isNull())
        {
            category = file_name.toStdString();
        }
        else{
            exit(0);
        }
    BMPDisplay w;
    bmpinfo inf;
    w.show();
    BMPRead(category);
    if(!Targethead.successfullyopened) w.setFixedSize(QSize(600,600));
    else {w.setFixedSize(QSize(Targetinfo.width,Targetinfo.height));
    QImage todisplayBMP(Targetinfo.width,Targetinfo.height, QImage::Format_RGB32);
    QColor colortemp;

    //此处根据位宽区别读取方法
    if(Targetinfo.pixelbit ==24){
        std::ifstream pixeldata(category,std::ios::in|std::ios::binary);
        for(int i=0;i<Targethead.shiftbyte;i++){pixeldata.get();}
        for(int j=Targetinfo.height-1;j>=0;j--){
            for(int i=0;i<=Targetinfo.width-1;i++){
                colortemp.setBlue(int(pixeldata.get()));
                colortemp.setGreen(int(pixeldata.get()));
                colortemp.setRed(int(pixeldata.get()));
                colortemp.setAlpha(255);
                todisplayBMP.setPixelColor(i,j,colortemp);
            }
            if((Targetinfo.width*3)%4!=0){
                for(int k = (Targetinfo.width*3)%4;k>0;k--){pixeldata.get();}
            }
        }
    }
    else if(Targetinfo.pixelbit ==16){
        int rawpixel16;
        std::ifstream pixeldata(category,std::ios::in|std::ios::binary);
        for(int i=0;i<Targethead.shiftbyte;i++){pixeldata.get();}
        if(Targetinfo.compassrate==0){ //555模式
            for(int j=Targetinfo.height-1;j>=0;j--){
                for(int i=0;i<=Targetinfo.width-1;i++){
                    byteflowreadint(&pixeldata,2,&rawpixel16);
                    colortemp.setRed((int((rawpixel16 & 0x7c00)>>10)+1)*8-1);
                    colortemp.setGreen((int((rawpixel16 & 0x03e0)>>5)+1)*8-1);
                    colortemp.setBlue((int(rawpixel16 & 0x001f)+1)*8-1);
                    colortemp.setAlpha(255);
                    todisplayBMP.setPixelColor(i,j,colortemp);
                }
            }
        }
        else{ //565模式
            for(int j=Targetinfo.height-1;j>=0;j--){
                for(int i=0;i<=Targetinfo.width-1;i++){
                    byteflowreadint(&pixeldata,2,&rawpixel16);
                    colortemp.setRed((int((rawpixel16 & 0xf800)>>11)+1)*8-1);
                    colortemp.setGreen((int((rawpixel16 & 0x07e0)>>5)+1)*8-1);
                    colortemp.setBlue((int(rawpixel16 & 0x001f)+1)*8-1);
                    colortemp.setAlpha(255);
                    todisplayBMP.setPixelColor(i,j,colortemp);
                }
            }
        }
    }
    else if(Targetinfo.pixelbit ==8){
        std::ifstream mapdata(category,std::ios::in|std::ios::binary);
        for(int i=0;i<54;i++){mapdata.get();}
        QColor mapcolortemp;
        for(int i=54;i<Targethead.shiftbyte;i+=4){
            mapcolortemp.setBlue(int(mapdata.get()));
            mapcolortemp.setGreen(int(mapdata.get()));
            mapcolortemp.setRed(int(mapdata.get()));
            mapcolortemp.setAlpha(int(mapdata.get()));
            colormap.push_back(mapcolortemp);
        }
        mapdata.close();
        std::ifstream pixeldata(category,std::ios::in|std::ios::binary);
        for(int i=0;i<Targethead.shiftbyte;i++){pixeldata.get();}
        for(int j=Targetinfo.height-1;j>=0;j--){
            for(int i=0;i<=Targetinfo.width-1;i++){
                todisplayBMP.setPixelColor(i,j,colormap[int(pixeldata.get())]);
            }
            if(Targetinfo.width%4!=0){ //4位对齐
                for(int k = Targetinfo.width%4;k>0;k--){pixeldata.get();}
            }
        }
    }
    else if(Targetinfo.pixelbit ==4){
        std::ifstream mapdata(category,std::ios::in|std::ios::binary);
        for(int i=0;i<54;i++){mapdata.get();}
        QColor mapcolortemp;
        for(int i=54;i<Targethead.shiftbyte;i+=4){
            mapcolortemp.setBlue(int(mapdata.get()));
            mapcolortemp.setGreen(int(mapdata.get()));
            mapcolortemp.setRed(int(mapdata.get()));
            mapcolortemp.setAlpha(int(mapdata.get()));
            colormap.push_back(mapcolortemp);
        }
        mapdata.close();
        std::ifstream pixeldata(category,std::ios::in|std::ios::binary);
        for(int i=0;i<Targethead.shiftbyte;i++){pixeldata.get();}
        int twopixelsbuffer;
        bool bufferempty = true;
        for(int j=Targetinfo.height-1;j>=0;j--){
            for(int i=0;i<=Targetinfo.width-1;i++){
                if(bufferempty){
                    twopixelsbuffer = int(pixeldata.get());
                    bufferempty = false;
                    todisplayBMP.setPixelColor(i,j,colormap[int(twopixelsbuffer & 0xf0)>>4]);
                    continue;
                }
                else{
                    todisplayBMP.setPixelColor(i,j,colormap[int(twopixelsbuffer & 0x0f)]);
                    bufferempty = true;
                    continue;
                }
            }
            int kongguo = Targetinfo.width%8; //4位对齐
            int yifenpei = kongguo/2;
            int yizairu = kongguo%2;
            if(yizairu==0) {
                for(int i=4-yifenpei;i>0;i--){pixeldata.get();}
            }
            else{
                for(int i=3-yifenpei;i>0;i--){pixeldata.get();}
            }
        }
    }
    else if(Targetinfo.pixelbit ==1){
        std::ifstream mapdata(category,std::ios::in|std::ios::binary);
        for(int i=0;i<54;i++){mapdata.get();}
        QColor mapcolortemp;
        for(int i=54;i<Targethead.shiftbyte;i+=4){
            mapcolortemp.setBlue(int(mapdata.get()));
            mapcolortemp.setGreen(int(mapdata.get()));
            mapcolortemp.setRed(int(mapdata.get()));
            mapcolortemp.setAlpha(int(mapdata.get()));
            colormap.push_back(mapcolortemp);
        }
        mapdata.close();
        std::ifstream pixeldata(category,std::ios::in|std::ios::binary);
        for(int i=0;i<Targethead.shiftbyte;i++){pixeldata.get();}
        deque<int> eightpixelsbuffer;
        for(int j=Targetinfo.height-1;j>=0;j--){
            for(int i=0;i<=Targetinfo.width-1;i++){
                    if (eightpixelsbuffer.empty()){
                        int temp = pixeldata.get();
                        eightpixelsbuffer.push_back((temp&0x80)>>7);
                        eightpixelsbuffer.push_back((temp&0x40)>>6);
                        eightpixelsbuffer.push_back((temp&0x20)>>5);
                        eightpixelsbuffer.push_back((temp&0x10)>>4);
                        eightpixelsbuffer.push_back((temp&0x08)>>3);
                        eightpixelsbuffer.push_back((temp&0x04)>>2);
                        eightpixelsbuffer.push_back((temp&0x02)>>1);
                        eightpixelsbuffer.push_back((temp&0x01));
                    }
                    todisplayBMP.setPixelColor(i,j,colormap[eightpixelsbuffer.front()]);
                    eightpixelsbuffer.pop_front();
                }
            int kongguo = Targetinfo.width%32; //4位对齐
            int yifenpei = kongguo/8;
            int yizairu = kongguo%8;
            if(yizairu==0) {
                for(int i=4-yifenpei;i>0;i--){pixeldata.get();}
            }
            else{
                for(int i=3-yifenpei;i>0;i--){pixeldata.get();}
            }
        }
    }
    else{
        qDebug()<<"Unsupported BMP bits!";
    }

    w.importpaintimage(todisplayBMP);
    w.show();
    inf.plotinit(&todisplayBMP);
    if(Targethead.successfullyopened){
        string wtw[75];
        wtw[0]="文件大小："+numtostr(Targethead.sizebyte)+"Bytes";
        wtw[1]="文件偏移量："+numtostr(Targethead.shiftbyte)+"Bytes";
        wtw[2]="图像宽度："+numtostr(Targetinfo.width)+"Pixels";
        wtw[3]="图像高度："+numtostr(Targetinfo.height)+"Pixels";
        wtw[4]="图像位宽："+numtostr(Targetinfo.pixelbit);
        wtw[5]="图像压缩率："+numtostr(Targetinfo.compassrate);
        wtw[6]="图像bi_size："+numtostr(Targetinfo.size)+"Bytes";
        wtw[7]="图像水平分辨率："+numtostr(Targetinfo.horizontalresolution)+"Pixels/metre";
        wtw[8]="图像垂直分辨率："+numtostr(Targetinfo.verticalresolution)+"Pixels/metre";
        wtw[9]="图像实际颜色索引："+numtostr(Targetinfo.acturalcolorindex);
        wtw[10]="图像重要颜色索引："+numtostr(Targetinfo.importantcolorindex);
        inf.bmpinfoprint(wtw);
    }
    inf.move(w.x()+w.width(),w.y());
    inf.show();
    }
    return a.exec();
}

void BMPRead(string source){ //BMP解码器
    unsigned char* thishead;
    std::ifstream bmpin(source,std::ios::in|std::ios::binary);
    if (!bmpin) {qDebug("File can not be opened");return;}

    //文件头读取与检查部分
    thishead = new unsigned char[2]; //读入前两位判断是否为BMP文件头
    for(int i=0;i<2;i++){
        *(thishead+i)=bmpin.get();
    }
    if (*thishead!='B'||*(thishead+1)!='M') {qDebug("Not a BMP file!");return;}
    delete thishead;

    thishead = new unsigned char[4]; //读入文件大小
    for(int i=0;i<4;i++){
        *(thishead+i)=bmpin.get();
    }
    CharReverse(thishead,4);
    Targethead.sizebyte=HexChartoint(thishead,4);
    delete thishead;

    thishead = new unsigned char[4]; //检查保留段完整性
    for(int i=0;i<4;i++){
        *(thishead+i)=bmpin.get();
        if (*(thishead+i)!=0) {qDebug("Reserve part ERROR");return;}
    }
    delete thishead;

    thishead = new unsigned char[4]; //读入偏移距离
    for(int i=0;i<4;i++){
        *(thishead+i)=bmpin.get();
    }
    CharReverse(thishead,4);
    Targethead.shiftbyte=HexChartoint(thishead,4);
    delete thishead;

    thishead = new unsigned char[4]; //检查位图信息头大小是否为40
    for(int i=0;i<4;i++){
        *(thishead+i)=bmpin.get();
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
    byteflowreadint(&bmpin,4,&Targetinfo.horizontalresolution);//读入水平分辨率
    byteflowreadint(&bmpin,4,&Targetinfo.verticalresolution);//读入垂直分辨率
    byteflowreadint(&bmpin,4,&Targetinfo.acturalcolorindex);//读入实际颜色索引数
    byteflowreadint(&bmpin,4,&Targetinfo.importantcolorindex);//读入重要颜色索引数

     Targethead.successfullyopened=true;
     bmpin.close();
}
void byteflowreadint(std::ifstream* source,int length,int* savelocation){
    unsigned char* temp = (unsigned char*)malloc(length*sizeof(unsigned char));
    for(int i=0;i<length;i++){
        *(temp+i)=source->get();
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
        toconverthex = toconverthex + myhex[decnum[0]] + myhex[decnum[1]];
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
