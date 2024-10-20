#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <qlist.h>
#include "ovalshape.h"  // 确保包含 OvalShape 的定义
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void UpdateOvalshapePos();
    void InitOvalshape();
    //熄灭流水灯 true{打开} false{熄灭}
    void toggleShapes(bool enabled);
protected:
    void setM1Shape();
    void setM2Shape();
    int m_currentM1Index; // 当前点亮的 M1 圆形索引
    int m_currentM2Index; // 当前点亮的 M2 圆形索引

private slots:
    void on_pb_send_clicked();

    void on_pb_openSp_clicked();

    void on_pb_closeSp_clicked();

    void on_pb_scan_clicked();

private:
    Ui::Dialog *ui;
    QList<QRect> m_lstLabelpos;
    QList<OvalShape*> m_ovalShapes;

    QList<OvalShape*> m_shapes; //温湿度等级
    QList<OvalShape*> m_M1_shapes; // M1 组
    QList<OvalShape*> m_M2_shapes; // M2 组
    QSerialPort* serialPort; //串口
    //控制流水灯的定时器
    QTimer* m_timer_M1M2;

protected:
    void initCOM();
    void scanAvailablePorts();
    void connectSerialPort();
    void disconnectSerialPort();
    void initBaudRateComboBox();

    //void sendMsg(QString& msg);             //字符模式 默认utf-8
    void sendBinaryData(int data);  //数值模式 默认int

private slots:
    void handle_readReady();

    void on_pb_ClearRecv_2_clicked();
};

// 定义宏，接受一个字符串作为输入
#define TRACEINFO_NO_ARG(message) \
ui->tb_info->append(QString("<INFO> %1").arg(message))



#endif // DIALOG_H
