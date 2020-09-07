#include "main.h"
#include "ui_qtserial.h"
#include <QDebug>
#include <QtSerialPort>
#include <QList>


QtSerial::QtSerial(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtSerial)
{
    ui->setupUi(this);



    //刷新定义的按钮状态
    mIsOpen = false;
    mIsOpenDtu = false;
    ui->BtWeight->setEnabled(mIsOpen);
    ui->BtSend->setEnabled(mIsOpen);
    ui->BtSetZeroRecv->setEnabled(mIsOpen);
    ui->BtSetZeroSend->setEnabled(mIsOpen);


    //识别当前系统有效串口号
    QList<QSerialPortInfo> serialPortInfo = QSerialPortInfo::availablePorts();//查看系统有哪些可用的UART
    //QList<qint32> standardBaudRates();

    if(serialPortInfo.isEmpty())
    {
        qDebug() << "当前没有可用串口";
        ui->cBoxName->addItem("无串口");
    }
    else
    {
        int count = serialPortInfo.count();
        for (int i=0; i < count; i++)
        {
            //qDebug() << serialPortInfo.size();//打印串口数量
            qDebug() << serialPortInfo.at(i).portName();//打印串口名字
            qDebug() << serialPortInfo.at(i).description();//打印串口描述

            ui->cBoxName->addItem(serialPortInfo.at(i).portName());//把识别的串口加到cBoxName中
            ui->cBoxDtu->addItem(serialPortInfo.at(i).portName());//把识别的串口加到cBoxDtu中
//            if(mSerialDtu.open(QIODevice::ReadWrite))
//            {
//                ui->cBoxDtu->addItem(serialPortInfo.at(i).portName());//把识别的串口加到cBoxDtu中
//                mSerialDtu.close();
//            }
        }
    }


    //窗口大小
    this->resize(800,450);
    qDebug() << "==============================";
    initDtuPort();

    ConnectShow();
}



QtSerial::~QtSerial()
{
    delete ui;
}

void QtSerial::ConnectShow()
{
    //连接串口信号和显示数据的槽函数
    connect(&mSerialPort, SIGNAL(readyRead()), this, SLOT(on_BtWeight_clicked()));
//    connect(&mSerialPort,  &QSerialPort::readyRead, this, &QtSerial::on_SerialPort_readyRead);


//    connect(&mSerialDtu, &QSerialPort::readyRead, this, &QtSerial::dtuSendData);
}


//串口初始化配置函数
bool QtSerial::getSerialPortConfig()
{
    qDebug() << "getSerialPortConfig" ;

    //获取串口配置
    mPortName = ui->cBoxName->currentText();
    mBaudRate = ui->cBoxBaudRate->currentText();
    mParity = ui->cBoxParity->currentText();
    mDateBits = ui->cBoxDateBits->currentText();
    mStopBits = ui->cBoxStopBits->currentText();

    //设置串口

    mSerialPort.setPortName(mPortName);    //端口号
    if("9600" == mBaudRate)
    {
        mSerialPort.setBaudRate(QSerialPort::Baud9600);
    }
    else
    {
        mSerialPort.setBaudRate(QSerialPort::Baud115200);
    }

    //校验位
    if("Even" == mParity)
    {
        mSerialPort.setParity(QSerialPort::EvenParity);
    }
    else if("odd" == mParity)
    {
        mSerialPort.setParity(QSerialPort::OddParity);
    }
    else
    {
        mSerialPort.setParity(QSerialPort::NoParity);
    }

    //数据位
    if("5" == mDateBits)
    {
        mSerialPort.setDataBits(QSerialPort::Data5);
    }
    else if("6" == mDateBits)
    {
        mSerialPort.setDataBits(QSerialPort::Data6);
    }
    else if("7" == mDateBits)
    {
        mSerialPort.setDataBits(QSerialPort::Data7);
    }
    else
    {
        mSerialPort.setDataBits(QSerialPort::Data8);
    }

    //停止位
    if("1.5" == mStopBits)
    {
        mSerialPort.setStopBits(QSerialPort::OneAndHalfStop);
    }
    else if("2" == mStopBits)
    {
        mSerialPort.setStopBits(QSerialPort::TwoStop);
    }
    else
    {
        mSerialPort.setStopBits(QSerialPort::OneStop);
    }

    return mSerialPort.open(QSerialPort::ReadWrite);
}

//
void QtSerial::initDtuPort()
{
    qDebug() << "initDtuPort";

    //获取串口配置
    mPortNameDtu = ui->cBoxDtu->currentText();
    mBaudRateDtu = ui->cBoxDBDtu->currentText();
    mParityDtu = ui->cBoxParityDtu->currentText();
    mDateBitsDtu = ui->cBoxBRdtu->currentText();
    mStopBitsDtu = ui->cBoxSBDtu->currentText();

    //设置串口

    mSerialDtu.setPortName(mPortNameDtu);    //端口号
    if("9600" == mBaudRateDtu)
    {
        mSerialDtu.setBaudRate(QSerialPort::Baud9600);
    }
    else
    {
        mSerialDtu.setBaudRate(QSerialPort::Baud115200);
    }

    //校验位
    if("Even" == mParityDtu)
    {
        mSerialDtu.setParity(QSerialPort::EvenParity);
    }
    else if("odd" == mParityDtu)
    {
        mSerialDtu.setParity(QSerialPort::OddParity);
    }
    else
    {
        mSerialDtu.setParity(QSerialPort::NoParity);
    }

    //数据位
    if("5" == mDateBitsDtu)
    {
        mSerialDtu.setDataBits(QSerialPort::Data5);
    }
    else if("6" == mDateBitsDtu)
    {
        mSerialDtu.setDataBits(QSerialPort::Data6);
    }
    else if("7" == mDateBitsDtu)
    {
        mSerialDtu.setDataBits(QSerialPort::Data7);
    }
    else
    {
        mSerialDtu.setDataBits(QSerialPort::Data8);
    }

    //停止位
    if("1.5" == mStopBitsDtu)
    {
        mSerialDtu.setStopBits(QSerialPort::OneAndHalfStop);
    }
    else if("2" == mStopBitsDtu)
    {
        mSerialDtu.setStopBits(QSerialPort::TwoStop);
    }
    else
    {
        mSerialDtu.setStopBits(QSerialPort::OneStop);
    }

}


void QtSerial::on_BtOpenDtu_clicked()
{
    qDebug() << "on_BtOpenDtu_clicked" ;

    //判断当前串口是否已经打开了，打开的话执行关闭动作
    if(true == mIsOpenDtu)
    {
        mSerialDtu.close();
        ui->BtOpenDtu->setText("打开");
        mIsOpenDtu = false;

        //其它选项进行禁止选项操作


        //其它选项进行打开选项操作
        ui->cBoxDtu->setEnabled(true);
        ui->cBoxParityDtu->setEnabled(true);
        ui->cBoxBRdtu->setEnabled(true);
        ui->cBoxDBDtu->setEnabled(true);
        ui->cBoxSBDtu->setEnabled(true);
    }
    else
    {
        //当前没有串口是打开的，进行打开操作
        if(true == mSerialDtu.open(QSerialPort::ReadWrite))
        {
            mIsOpenDtu = true;
            ui->BtOpenDtu->setText("关闭");
            qDebug() << "DTU串口打开成功" ;

            //其它选项进行打开选项操作


            //其它选项进行禁止选项操作
            ui->cBoxDtu->setEnabled(false);
            ui->cBoxParityDtu->setEnabled(false);
            ui->cBoxBRdtu->setEnabled(false);
            ui->cBoxDBDtu->setEnabled(false);
            ui->cBoxSBDtu->setEnabled(false);

//            while (!mSerialDtu.atEnd())
//            {

//            }
            int flg = mSerialDtu.write(senData.toUtf8());
            qDebug() << "flg = " << flg;
//            mSerialDtu.writeData(senData.toStdString().data(), senData.length());
            qDebug() << "senData.toUtf8()" << senData.toUtf8();
//            Delay_MSec(1000);

        }
        else
        {
            qDebug() << "DTU串口打开失败" ;
        }
    }
     //ui->BtOpenDtu->setEnabled(mIsOpenDtu);
}

//void QtSerial::dtuSendData(QString sData)
//{
//    if(mIsOpenDtu == true)
//    {
//       mSerialDtu.write(sData);
//        qDebug() << "mSerialDtu.write(senData)" << sData;
//    }
//}

void QtSerial::on_BtOpen_clicked()
{
    qDebug() << "on_btOpen_clicked" ;
    //判断当前串口是否已经打开了，打开的话执行关闭动作
    if(true == mIsOpen)
    {
        mSerialPort.close();
        ui->BtOpen->setText("打开");
        mIsOpen = false;

        //其它选项进行禁止选项操作
        ui->BtWeight->setEnabled(mIsOpen);
        ui->BtSetZeroRecv->setEnabled(mIsOpen);
        ui->BtSend->setEnabled(mIsOpen);
        ui->BtSetZeroRecv->setEnabled(mIsOpen);
        ui->BtSetZeroSend->setEnabled(mIsOpen);

        //其它选项进行打开选项操作
        ui->cBoxName->setEnabled(true);
        ui->cBoxParity->setEnabled(true);
        ui->cBoxBaudRate->setEnabled(true);
        ui->cBoxDateBits->setEnabled(true);
        ui->cBoxStopBits->setEnabled(true);
    }
    else
    {
        //当前没有串口是打开的，进行打开操作
        if(true == getSerialPortConfig())
        {
            mIsOpen = true;
            ui->BtOpen->setText("关闭");
            qDebug() << "串口打开成功" ;

            //其它选项进行打开选项操作
            ui->BtWeight->setEnabled(mIsOpen);
            ui->BtSetZeroRecv->setEnabled(mIsOpen);
            ui->BtSend->setEnabled(mIsOpen);
            ui->BtSetZeroRecv->setEnabled(mIsOpen);
            ui->BtSetZeroSend->setEnabled(mIsOpen);


            //其它选项进行禁止选项操作
            ui->cBoxName->setEnabled(false);
            ui->cBoxParity->setEnabled(false);
            ui->cBoxBaudRate->setEnabled(false);
            ui->cBoxDateBits->setEnabled(false);
            ui->cBoxStopBits->setEnabled(false);

//            mSerialPort.readLine();
        }
        else
        {
            qDebug() << "串口打开失败" ;
        }
    }
}


//数据接收和处理
QString QtSerial::on_BtWeight_clicked()
{
    //memset(mDataBuf, 0, sizeof (mDataBuf));
    if(true == mIsOpen)
    {

        qDebug() << "start" << endl;
        while (!mSerialPort.atEnd())
        {
            qDebug() << " while start" << endl;
            Sleep(100);
            //读取串口数据
            QByteArray recvData = mSerialPort.readAll();

            QString sysTime;//定义系统时间变量

            sysTime = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss\n");
            //进行数据处理，判断是否为空
            if(recvData.isNull())
            {

                qDebug() << "isnull";
            }
            else
            {
                //去除空行
                QString str = recvData.trimmed();
//                if(str.isEmpty()) {ui->textSendData->appendPlainText("nininini");};
//                 QString str = recvData.simplified();

                //只保留重量信息
                str = str.left(6).simplified();
                //判断是否超过10千克
                if(str.length() == 4)
                {
                    if(str  == "FULL")//判断是否超过30Kg
                    {
                        ui->textData->appendPlainText("too height");
                    }
                    else
                    {
                        str = str.insert(1, '.');//在第一位数字后面插入小数点
                        ui->textData->appendPlainText(str + " Kg");
                        ui->textData->appendPlainText(sysTime);
                        senData = str + "_____" + sysTime;
//                        qDebug() << "enData = str + sysTime;" << senData;
//                        qDebug() << recvData;
                    }

                }
                else
                {
                    str = str.insert(2, '.');//在第二位数字后面插入小数点
                    ui->textData->appendPlainText(str + " Kg");
                    ui->textData->appendPlainText(sysTime);
                    senData = str + "_____" +  sysTime;
//                    qDebug() << "enData = str + sysTime = " << senData;
//                    qDebug() << recvData;
                }


            }

        }

    }
    return senData;
}

//串口读取数据函数（未用到）
void QtSerial::on_SerialPort_readyRead()
{

    if(true == mIsOpen)
    {
//        qDebug() << "on_SerialPort_readyRead" ;
//        QByteArray recvData = mSerialPort.readAll();
////        ui->textData->appendPlainText(QString(recvData));
////        ui->textData->appendPlainText("QString(recvData)");
//        QString str = recvData.trimmed();
////      QString str = recvData.simplified();
////        int numbuf = str.left(5).toInt();
////         str = QString::number(numbuf, '.', 0);
//        ui->textData->appendPlainText(str);
//        qDebug() << recvData ;
//        QString sData = recvData ;
//        qDebug() << sData << endl;
    }
    else
    {
        qDebug() << "dont open serial";
    }

}

void QtSerial::on_BtSetZeroRecv_clicked()
{
    qDebug() << "on_BtSetZeroRecv_clicked" ;
    ui->textData->clear();

}

void QtSerial::on_BtSetZeroSend_clicked()
{
    qDebug() << "on_BtSetZeroSend_clicked" ;
    ui->textSendData->clear();
}


void QtSerial::on_BtSend_clicked()
{
    if(true == mIsOpen)
    {
        QString sdata = ui->textSendData->toPlainText();
        QByteArray fdata = sdata.toLatin1();
        char * temp = fdata.data();
        mSerialPort.write(temp);
    }

}
void  QtSerial::Sleep(int msec)
{
    QTime dTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < dTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

