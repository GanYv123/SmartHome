#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
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
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QSerialPort* serialPort;

protected:
    void initCOM();
    void scanAvailablePorts();
    void connectSerialPort();
    void disconnectSerialPort();
    void initBaudRateComboBox();

    void sendMsg(QString& msg);

private slots:
    void on_pushButton_scan_clicked();
    void on_pushButton_connetCOM_clicked();
    void on_pushButton_disconnet_clicked();
    void on_pushButton_send_clicked();
    void handle_readReady();
    void on_pushButton_ClearRecv_clicked();
};
#endif // DIALOG_H
