#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    /* 兼容高分辨率屏幕 */
#if (QT_VERSION > QT_VERSION_CHECK(5,6,0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}
