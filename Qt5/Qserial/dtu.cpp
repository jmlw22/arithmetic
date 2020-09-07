//#include "main.h"

//void QtSerial::on_BtOpenDtu_clicked()
//{

//}



//void QtSerial::initDtuPort()
//{
//    qDebug() << "initDtuPort";

//    //获取串口配置
//    mPortNameDtu = ui->cBoxDtu->currentText();
//    mBaudRateDtu = ui->cBoxDBDtu->currentText();
//    mParityDtu = ui->cBoxParityDtu->currentText();
//    mDateBitsDtu = ui->cBoxBRdtu->currentText();
//    mStopBitsDtu = ui->cBoxSBDtu->currentText();

//    //设置串口

//    mSerialDtu.setPortName(mPortNameDtu);    //端口号
//    if("9600" == mBaudRateDtu)
//    {
//        mSerialDtu.setBaudRate(QSerialPort::Baud9600);
//    }
//    else
//    {
//        mSerialDtu.setBaudRate(QSerialPort::Baud115200);
//    }

//    //校验位
//    if("Even" == mParityDtu)
//    {
//        mSerialDtu.setParity(QSerialPort::EvenParity);
//    }
//    else if("odd" == mParityDtu)
//    {
//        mSerialDtu.setParity(QSerialPort::OddParity);
//    }
//    else
//    {
//        mSerialDtu.setParity(QSerialPort::NoParity);
//    }

//    //数据位
//    if("5" == mDateBitsDtu)
//    {
//        mSerialDtu.setDataBits(QSerialPort::Data5);
//    }
//    else if("6" == mDateBitsDtu)
//    {
//        mSerialDtu.setDataBits(QSerialPort::Data6);
//    }
//    else if("7" == mDateBitsDtu)
//    {
//        mSerialDtu.setDataBits(QSerialPort::Data7);
//    }
//    else
//    {
//        mSerialDtu.setDataBits(QSerialPort::Data8);
//    }

//    //停止位
//    if("1.5" == mStopBitsDtu)
//    {
//        mSerialDtu.setStopBits(QSerialPort::OneAndHalfStop);
//    }
//    else if("2" == mStopBitsDtu)
//    {
//        mSerialDtu.setStopBits(QSerialPort::TwoStop);
//    }
//    else
//    {
//        mSerialDtu.setStopBits(QSerialPort::OneStop);
//    }

//}


