#include "dialog.h"
#include "ui_dialog.h"
#include "OvalShape.h"
#include <qdebug.h>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->checkBox->setStyleSheet(
        "QCheckBox::indicator { width: 26px; height: 26px; }"  // 设置指示器的大小
        "QCheckBox::indicator:unchecked { background: yellow; border: 1px solid black; }"  // 未选中时的样式
        "QCheckBox::indicator:checked { background: black; }"
        );  // 选中时的样式
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

void Dialog::on_pb_send_clicked()
{
    toggleShapes(false);
    qDebug()<<m_shapes.size();
}

