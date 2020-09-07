#include "main.h"
#include <QMessageBox>
#include <QTimer>
#include <QHostAddress>
//#include <wiringPi.h>
#include <QEventLoop>

//int temp;
//void callback(){
//    temp++;
//    qDebug()<<"temp="<<temp;
//}

//void QtSerial::SandData(){
//    int com=temp;
//    Delay_MSec(4500);
//    if(temp!=com){
//        QString str="1";
//        tcpSocket->write(str.toUtf8().data());
//        qDebug()<<com;
//    }
//}

//void QtSerial::initRasIO(){
//    pinMode(G17,OUTPUT);
//    pinMode(G18,OUTPUT);
//}

//void QtSerial::Delay_MSec(unsigned int msec){
//    QEventLoop loop;//定义一个新的事件循环
//    QTimer::singleShot(msec, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
//    loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
//}
