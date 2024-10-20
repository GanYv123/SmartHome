#include "dialog.h"
#include "ui_dialog.h"
#include "OvalShape.h"
#include <QMessageBox>
#include <qdebug.h>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , serialPort(nullptr)
{
    ui->setupUi(this);
    ui->checkBox->setStyleSheet(
        "QCheckBox::indicator { width: 26px; height: 26px; }"  // 设置指示器的大小
        "QCheckBox::indicator:unchecked { background: yellow; border: 1px solid black; }"  // 未选中时的样式
        "QCheckBox::indicator:checked { background: black; }"
        );  // 选中时的样式

    ui->pb_send->setEnabled(false);
    ui->pb_closeSp->setEnabled(false);

    initCOM();
    InitOvalshape();
    UpdateOvalshapePos();
}

Dialog::~Dialog()
{
    delete ui; // 确保 ui 指针被释放
}


void Dialog::setM1Shape() {
    for (int i = 4; i < 8; ++i) { // M1 从索引 4 到 7
        if (i == m_currentM1Index + 4) { // 加 4 因为 M1 从 m_shapes[4] 开始
            m_shapes[i]->setColor(Qt::green); // 点亮
        } else {
            m_shapes[i]->setColor(Qt::white); // 熄灭
        }
    }
    m_currentM1Index = (m_currentM1Index + 1) % 4; // 循环更新索引
}

void Dialog::setM2Shape() {
    for (int i = 8; i < 12; ++i) { // M2 从索引 8 到 11
        if (i == m_currentM2Index + 8) { // 加 8 因为 M2 从 m_shapes[8] 开始
            m_shapes[i]->setColor(Qt::green); // 点亮
        } else {
            m_shapes[i]->setColor(Qt::white); // 熄灭
        }
    }
    m_currentM2Index = (m_currentM2Index + 1) % 4; // 循环更新索引
}

void Dialog::UpdateOvalshapePos()
{
    // todo:这里更新椭圆形的位置，或者根据需要添加额外逻辑
}

void Dialog::InitOvalshape()
{
    // 设置参数
    int radius = 15; // 圆的半径
    int spacing = 30; // 圆之间的间隔

    // 创建四个 OvalShape 实例并直接添加到 QList
    m_shapes.append(new OvalShape(radius, this));
    m_shapes.append(new OvalShape(radius, this));
    m_shapes.append(new OvalShape(radius, this));
    m_shapes.append(new OvalShape(radius, this));

    // 设置颜色
    m_shapes[0]->setColor(Qt::white);
    m_shapes[1]->setColor(Qt::white);
    m_shapes[2]->setColor(Qt::white);
    m_shapes[3]->setColor(Qt::white);

    int diameter = 2 * radius; // 圆的直径
    int startX = 120; // 起始 x 坐标
    int pos_y = 25; // y 坐标

    // 计算每个圆心的 X 坐标
    int x1 = startX; // 第一个圆的 x 坐标
    int x2 = x1 + diameter + spacing; // 第二个圆的 x 坐标
    int x3 = x2 + diameter + spacing; // 第三个圆的 x 坐标
    int x4 = x3 + diameter + spacing; // 第四个圆的 x 坐标

    // 设置每个圆的中心位置
    m_shapes[0]->setCenter(QPoint(x1 + radius, pos_y)); // y 坐标可根据需求调整
    m_shapes[1]->setCenter(QPoint(x2 + radius, pos_y));
    m_shapes[2]->setCenter(QPoint(x3 + radius, pos_y));
    m_shapes[3]->setCenter(QPoint(x4 + radius, pos_y));

    // 显示圆形
    m_shapes[0]->show();
    m_shapes[1]->show();
    m_shapes[2]->show();
    m_shapes[3]->show();

    // 设置 M1 和 M2 的位置
    QPoint positionsM1[4] = {
        QPoint(42.5, 85),    // M1 圆形 1
        QPoint(85, 42.5),    // M1 圆形 2
        QPoint(127.5, 85), // M1 圆形 3
        QPoint(85, 127.5)    // M1 圆形 4
    };

    // 创建 M1 组的 OvalShape 实例并设置颜色和位置
    for (int i = 0; i < 4; ++i) {
        OvalShape* shape = new OvalShape(radius, ui->groupBox); // 创建 OvalShape
        shape->setColor(Qt::white); // 设置颜色
        shape->setCenter(positionsM1[i]); // 设置中心位置
        shape->show(); // 显示圆形
        m_shapes.append(shape); // 添加到 QList
    }

    // 设置 M2 的位置，假设 M2 和 M1 的位置相同
    QPoint positionsM2[4] = {
        QPoint(42.5, 85),    // M2 圆形 1
        QPoint(85, 42.5),    // M2 圆形 2
        QPoint(127.5, 85), // M2 圆形 3
        QPoint(85, 127.5)    // M2 圆形 4
    };

    // 创建 M2 组的 OvalShape 实例并设置颜色和位置
    for (int i = 0; i < 4; ++i) {
        OvalShape* shape = new OvalShape(radius, ui->groupBox_2); // 创建 OvalShape
        shape->setColor(Qt::white); // 设置颜色
        shape->setCenter(positionsM2[i]); // 设置中心位置
        shape->show(); // 显示圆形
        m_shapes.append(shape); // 添加到 QList
    }

    // 设置定时器
    m_timer_M1M2 = new QTimer(this);
    connect(m_timer_M1M2, &QTimer::timeout, this, [=]() {
        setM1Shape(); // 更新 M1 形状状态
        setM2Shape(); // 更新 M2 形状状态
    });
    m_timer_M1M2->start(500); // 每 500 毫秒更新一次

    TRACEINFO_NO_ARG("完成图形初始化");
}

void Dialog::toggleShapes(bool enabled) {
    if (enabled) {
        m_timer_M1M2->start(500); // 启动定时器
    } else {
        m_timer_M1M2->stop(); // 停止定时器
        for (int i = 4; i <11; ++i) {
            m_shapes[i]->setColor(Qt::white); // 熄灭所有
        }
    }
}

//发送内容
void Dialog::on_pb_send_clicked()
{
    //todo:发送内容到下位机
    int val = ui->spinBox->value();
    ui->tb_info->append(QString("<DEBUG>Send val:%1").arg(val));
    sendBinaryData(val);
}

void Dialog::initCOM()
{
    //串口初始化
    if(serialPort == nullptr)
        serialPort = new QSerialPort(this);
    scanAvailablePorts();
    initBaudRateComboBox();
     connect(this->serialPort, &QSerialPort::readyRead, this, &Dialog::handle_readReady);
}

void Dialog::scanAvailablePorts()
{
    ui->comboBox_COM_2->clear();
    // 获取所有可用串口
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    // 遍历可用串口
    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        // 将串口名称添加到下拉选择框中
        ui->comboBox_COM_2->addItem(serialPortInfo.portName());
    }
    // 如果没有可用串口，提示用户
    if (serialPortInfos.isEmpty()) {
        ui->comboBox_COM_2->addItem("No available ports");
    }

    ui->tb_info->append(QString("<INFO>扫描到 %1 个串口").arg(serialPortInfos.size()));
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
    QString selectedPort = ui->comboBox_COM_2->currentText();

    if (selectedPort.isEmpty() || selectedPort == "No available ports") {
        QMessageBox::warning(this, "Error", "No valid COM port selected");
        return;
    }
    // 获取用户选择的波特率
    int baudRate = ui->comboBox_baudRate_2->currentText().toInt(); // 从下拉框中获取波特率
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
    ui->pb_openSp->setEnabled(false);
    ui->pb_send->setEnabled(true);
    ui->pb_closeSp->setEnabled(true);

    //更新combox属性
    ui->comboBox_baudRate_2->setDisabled(true);
    ui->comboBox_COM_2->setDisabled(true);
}

void Dialog::disconnectSerialPort()
{
    if (serialPort->isOpen()) {
        serialPort->close();  // 关闭串口
        QMessageBox::information(this, "Success", "Port disconnected successfully!");

        // 更新按钮状态
        ui->pb_send->setEnabled(false);
        ui->pb_closeSp->setEnabled(false);
        ui->pb_openSp->setEnabled(true);
        //更新combox属性
        ui->comboBox_baudRate_2->setDisabled(false);
        ui->comboBox_COM_2->setDisabled(false);
        TRACEINFO_NO_ARG("关闭串口成功！");
    } else {
        QMessageBox::warning(this, "Warning", "No port is currently open.");
    }
}

void Dialog::initBaudRateComboBox()
{
    // 获取下拉框对象
    QComboBox* baudRateComboBox = ui->comboBox_baudRate_2;

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
        ui->tb_info->append(QString("<DEBUG> write ret:%1").arg(ret));
        TRACEINFO_NO_ARG("发送数据成功！");
        if(ret == -1){
            QMessageBox::critical(this, "Error", "Failed to send binary data to serial port.");
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning", "串口未打开，请先连接串口");
    }
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
        // 使用 QDataStream 处理二进制数据
        static QByteArray buffer; // 使用静态缓冲区以确保接收到的数据是完整的
        buffer.append(data); // 添加接收到的数据到缓冲区

        // 判断是否有足够的数据（例如 4 字节整数）
        const int INT_SIZE = sizeof(int);

        while (buffer.size() >= INT_SIZE)
        {
            QByteArray intData = buffer.left(INT_SIZE);
            buffer.remove(0, INT_SIZE); // 移除已处理的部分

            // 使用 QDataStream 读取整数
            QDataStream stream(intData);
            stream.setByteOrder(QDataStream::LittleEndian); // 确保字节顺序一致
            int number;
            stream >> number;
            // 在 QTextBrowser 中显示接收到的整数数据
            ui->tb_info->append("Received <INFO>: " + QString::number(number));
        }

    } else {
        QMessageBox::warning(this, "Warning", "Serial port is not open.");
    }
}


//连接串口
void Dialog::on_pb_openSp_clicked()
{
    connectSerialPort();
}

//断开连接
void Dialog::on_pb_closeSp_clicked()
{
    disconnectSerialPort();
}

//扫描串口
void Dialog::on_pb_scan_clicked()
{
    scanAvailablePorts();
}

//清空日志
void Dialog::on_pb_ClearRecv_2_clicked()
{
    ui->tb_info->clear();
}

