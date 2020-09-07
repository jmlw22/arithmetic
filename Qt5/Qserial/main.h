#ifndef MAIN_H
#define MAIN_H

#include <QMainWindow>
#include <QSerialPort>//提供串口访问功能
#include <QSerialPortInfo>//提供系统中存在的串口信息
#include <QTcpServer>  //监听套接字
#include <QTcpSocket>  //通讯套接字
//#include <wiringPi.h>////树莓派管脚库

#define G17 0  //G17
#define G18 1  //G18
#define G24 5

#define pul_y 27 //G16
#define dir_y 24 //G19
#define check_y 6//G25

#define pul_z 23 //G13
#define dir_z 28 //G20

#define pul_c 26 //G12
#define dir_c 29 //G21

QT_BEGIN_NAMESPACE
namespace Ui { class QtSerial; }
QT_END_NAMESPACE

class QtSerial : public QMainWindow
{
    Q_OBJECT

public:
    QtSerial(QWidget *parent = nullptr);
    ~QtSerial();

public:
    //电子秤串口初始化配置
    bool getSerialPortConfig(void);

    //
    void initDtuPort(void);

    void dtuSendData(QString sData);

    void ConnectShow();

    //RFID模块设置
    void initWidget();
    void readRFID();
    void initTcp();
    void SandData();
    void initRasIO();
    void Delay_MSec(unsigned int msec);
    
private slots:

    //电子秤串口模块
    //重量按钮
    QString on_BtWeight_clicked();
    //串口读数据
    void on_SerialPort_readyRead();
    //接收清零
    void on_BtSetZeroRecv_clicked();
    //打开按钮
    void on_BtOpen_clicked();
    //发送按钮
    void on_BtSend_clicked();
    //延时函数，参数为毫秒
    void Sleep(int msec);
    //发送清零
    void on_BtSetZeroSend_clicked();


    void on_BtOpenDtu_clicked();

private:
    Ui::QtSerial *ui;

    //电子秤串口模块
    bool mBtnStatus;//按钮状态
    bool mIsOpen;//串口状态
    bool mIsOpenDtu;
    //QstrialPort * mSerialPort = new QSerialPort;

    QSerialPort mSerialPort; //串口实例化
    QSerialPort mSerialDtu;

    QString mPortName;//串口名
    QString mBaudRate;//波特率
    QString mParity;//校正位
    QString mDateBits;//数据位
    QString mStopBits;//停止位

    QString mPortNameDtu;//串口名
    QString mBaudRateDtu;//波特率
    QString mParityDtu;//校正位
    QString mDateBitsDtu;//数据位
    QString mStopBitsDtu;//停止位

    QString senData;
    QChar mDataBuf[64];//数据缓存区

    //RFID模块
    QSerialPort *serial;
    QString rec;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;

};
#endif // QTSERIAL_H
