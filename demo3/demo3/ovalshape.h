#ifndef OVALSHAPE_H
#define OVALSHAPE_H

#include <QWidget>
#include <QPainter>
#include <QColor>

class OvalShape : public QWidget
{
    Q_OBJECT

public:
    explicit OvalShape(QWidget *parent = nullptr); // 构造函数
    OvalShape(int radius, QWidget *parent);
    void setColor(const QColor &color);              // 设置颜色
    void setRadius(int radius);                      // 设置半径
    void setCenter(const QPoint& center);            // 设置圆心

    int radius() const { return m_radius; }         // 获取当前半径

protected:
    void paintEvent(QPaintEvent *event) override;   // 重写绘制事件

private:
    QColor m_color;  // 颜色变量
    int m_radius;    // 半径
    QPoint m_center; // 圆心
};

#endif // OVALSHAPE_H
