#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    // 更新按钮状态
    ui->pushButton_connetCOM->setEnabled(true);
    ui->pushButton_disconnet->setEnabled(false);
    serialPort = new QSerialPort(this);
    initCOM();
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    // 如果是Qt6版本，使用新的connect语法
    connect(this->serialPort, &QSerialPort::readyRead, this, &Dialog::handle_readReady);
#else
    // 如果是Qt5版本，使用旧的connect语法
    connect(this->serialPort, SIGNAL(readyRead()), this, SLOT(handle_readReady()));
#endif
}

Dialog::~Dialog()
{
    delete ui;
    delete serialPort;
}

/**
 * @brief 初始化com选择框内容
 */
void Dialog::initCOM()
{
    scanAvailablePorts();
    initBaudRateComboBox();
}

void Dialog::initBaudRateComboBox()
{
    // 获取下拉框对象
    QComboBox* baudRateComboBox = ui->comboBox_baudRate;

    // 清空之前的内容
    baudRateComboBox->clear();

    // 添加常用波特率
    QList<int> baudRates = {9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600};

    for (int rate : baudRates) {
        baudRateComboBox->addItem(QString::number(rate), rate);  // 显示波特率并存储其值
    }

    // 设置默认选择的波特率，例如9600
    baudRateComboBox->setCurrentIndex(baudRates.indexOf(9600));
}

void Dialog::sendMsg(QString &msg)
{
    if (serialPort->isOpen())
    {
        // 添加换行符以标记消息结束
        msg.append("\n");

        // 通过串口发送数据
        qint64 ret = serialPort->write(msg.toUtf8());
        if(ret == -1){
            QMessageBox::critical(this, "Error", "Failed to send data to serial port.");
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning", "串口未打开，请先连接串口");
    }
}

void Dialog::sendBinaryData(int data)
{
    if (serialPort->isOpen())
    {
        // 将整数数据转换为字节数组
        QByteArray byteArray;
        QDataStream stream(&byteArray, QIODevice::WriteOnly);

        //默认为大端
        stream.setByteOrder(QDataStream::LittleEndian);

        // 写入整数数据到字节流
        stream << data;

        // 通过串口发送数据
        qint64 ret = serialPort->write(byteArray);
        if(ret == -1){
            QMessageBox::critical(this, "Error", "Failed to send binary data to serial port.");
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning", "串口未打开，请先连接串口");
    }
}

void Dialog::scanAvailablePorts()
{
    ui->comboBox_COM->clear();
    // 获取所有可用串口
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    // 遍历可用串口
    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        // 将串口名称添加到下拉选择框中
        ui->comboBox_COM->addItem(serialPortInfo.portName());
    }
    // 如果没有可用串口，提示用户
    if (serialPortInfos.isEmpty()) {
        ui->comboBox_COM->addItem("No available ports");
    }
    ui->label_status->setText(QString("扫描到 %1 个串口").arg(serialPortInfos.size()));
}

void Dialog::connectSerialPort()
{
    // 确保串口未打开
    if (serialPort->isOpen()) {
        QMessageBox::warning(this, "Warning", "端口已打开");
        serialPort->close();
        return;
    }

    // 获取用户选择的串口
    QString selectedPort = ui->comboBox_COM->currentText();

    if (selectedPort.isEmpty() || selectedPort == "No available ports") {
        QMessageBox::warning(this, "Error", "No valid COM port selected");
        return;
    }
    // 获取用户选择的波特率
    int baudRate = ui->comboBox_baudRate->currentText().toInt(); // 从下拉框中获取波特率
    // 配置串口
    serialPort->setPortName(selectedPort);
    serialPort->setBaudRate(baudRate);  // 选择合适的波特率
    // serialPort->setDataBits(QSerialPort::Data8);     // 数据位
    // serialPort->setParity(QSerialPort::NoParity);    // 校验位
    // serialPort->setStopBits(QSerialPort::OneStop);   // 停止位
    // serialPort->setFlowControl(QSerialPort::NoFlowControl); // 流控制
    /**
     *  数据位（Data Bits）：默认是 QSerialPort::Data8（8个数据位）。
        校验位（Parity）：默认是 QSerialPort::NoParity（无校验）。
        停止位（Stop Bits）：默认是 QSerialPort::OneStop（1个停止位）。
        流控制（Flow Control）：默认是 QSerialPort::NoFlowControl（无流控制）
    */

    // 打开串口
    if (!serialPort->open(QIODevice::ReadWrite)) {
        QMessageBox::critical(this, "Error", "Failed to open port!");
        return;
    }

    QMessageBox::information(this, "Success", "Port opened successfully!");

    // 更新按钮状态
    ui->pushButton_connetCOM->setEnabled(false);    // 禁用连接按钮
    ui->pushButton_disconnet->setEnabled(true);  // 启用断开按钮
    //更新combox属性
    ui->comboBox_baudRate->setDisabled(true);
    ui->comboBox_COM->setDisabled(true);
}

void Dialog::disconnectSerialPort()
{
    if (serialPort->isOpen()) {
        serialPort->close();  // 关闭串口
        QMessageBox::information(this, "Success", "Port disconnected successfully!");

        // 更新按钮状态
        ui->pushButton_connetCOM->setEnabled(true);
        ui->pushButton_disconnet->setEnabled(false);
        //更新combox属性
        ui->comboBox_baudRate->setDisabled(false);
        ui->comboBox_COM->setDisabled(false);
    } else {
        QMessageBox::warning(this, "Warning", "No port is currently open.");
    }
}

void Dialog::on_pushButton_scan_clicked()
{
    scanAvailablePorts();
}


void Dialog::on_pushButton_connetCOM_clicked()
{
    connectSerialPort();
}


void Dialog::on_pushButton_disconnet_clicked()
{
    disconnectSerialPort();
}

void Dialog::on_pushButton_send_clicked()
{
    // 获取输入区的内容
    QString input = ui->textBrowser->toPlainText();

    // 检查是否选中了字符发送模式
    if(ui->radioButton->isChecked()){
        // 数值发送模式
        bool ok;
        // 这里假设你想发送整数，你可以根据需要改成其他类型
        int number = input.toInt(&ok);

        if(ok) {
            // 如果转换成功，发送数值数据
            sendBinaryData(number);
        } else {
            QMessageBox::warning(this, "Warning", "输入的内容不是有效的整数");
        }
    } else {
        // 字符发送模式
        sendMsg(input);
    }

    // 清空输入区
    ui->textBrowser->clear();
}


/**
 * @brief Dialog::handle_readReady
 * @todo 串口通信是异步的，数据可能会分片到达，因此需要进行缓冲和处理
 */
void Dialog::handle_readReady()
{
    if (serialPort->isOpen()) {
        // 读取串口数据
        QByteArray data = serialPort->readAll();

        // 根据选择的模式处理数据
        if (ui->radioButton->isChecked()) { // 数值模式
            // 使用 QDataStream 处理二进制数据
            static QByteArray buffer; // 使用静态缓冲区以确保接收到的数据是完整的
            buffer.append(data); // 添加接收到的数据到缓冲区

            // 判断是否有足够的数据（例如 4 字节整数）
            const int INT_SIZE = sizeof(int);
            while (buffer.size() >= INT_SIZE) {
                QByteArray intData = buffer.left(INT_SIZE);
                buffer.remove(0, INT_SIZE); // 移除已处理的部分

                // 使用 QDataStream 读取整数
                QDataStream stream(intData);
                stream.setByteOrder(QDataStream::LittleEndian); // 确保字节顺序一致
                int number;
                stream >> number;

                // 在 QTextBrowser 中显示接收到的整数数据
                ui->textBrowser_2->append("Received (Number): " + QString::number(number));
            }
        } else if (ui->radioButton_2->isChecked()) { // 字符模式
            // 处理字符数据
            static QByteArray charBuffer; // 字符模式的缓冲区
            charBuffer.append(data); // 添加数据到字符缓冲区

            // 查找换行符，确保每次完整地接收并显示一行数据
            int endIndex = charBuffer.indexOf('\n');
            while (endIndex != -1) {
                QByteArray completeMessage = charBuffer.left(endIndex); // 获取完整消息
                charBuffer.remove(0, endIndex + 1); // 移除已处理的消息

                // 将数据转换为字符串
                QString receivedData = QString::fromUtf8(completeMessage.trimmed()); // 移除前后的空白符，包括 \r

                // 在 QTextBrowser 中显示接收到的字符数据
                ui->textBrowser_2->append("Received (Text): " + receivedData);

                // 继续查找下一个换行符
                endIndex = charBuffer.indexOf('\n');
            }
        }
    } else {
        QMessageBox::warning(this, "Warning", "Serial port is not open.");
    }
}

void Dialog::on_pushButton_ClearRecv_clicked()
{
    ui->textBrowser_2->clear();
}

