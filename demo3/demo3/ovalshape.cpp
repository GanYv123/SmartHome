#include "ovalshape.h"
#include <QPainter>

OvalShape::OvalShape(QWidget *parent)
    : QWidget(parent), m_color(Qt::green), m_radius(30), m_center(0, 0)
{
    setFixedSize(2 * m_radius, 2 * m_radius);  // 设置固定大小为直径
}

OvalShape::OvalShape(int radius, QWidget *parent)
    : QWidget(parent), m_color(Qt::green), m_radius(radius), m_center(0, 0)
{
    setFixedSize(2 * m_radius, 2 * m_radius);  // 设置固定大小为直径
}

void OvalShape::setColor(const QColor &color)
{
    m_color = color;  // 设置颜色
    update();         // 触发重绘
}

void OvalShape::setRadius(int radius)
{
    m_radius = radius; // 设置半径
    setFixedSize(2 * m_radius, 2 * m_radius); // 根据半径设置大小
    update();         // 触发重绘
}

void OvalShape::setCenter(const QPoint& center)
{
    m_center = center; // 设置圆心
    int x = m_center.x() - m_radius; // 左上角 x
    int y = m_center.y() - m_radius; // 左上角 y
    setGeometry(x, y, 2 * m_radius, 2 * m_radius); // 设置几何形状
    update();         // 触发重绘
}

void OvalShape::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBrush(m_color);
    painter.setPen(Qt::NoPen);  // 不绘制边框
    painter.drawEllipse(QPoint(m_radius, m_radius), m_radius, m_radius); // 绘制圆
}
