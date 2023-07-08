#include <QApplication>
#include <QDir>
#include <QFile>
#include "styles/dark_style.h"
#include "test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(new DarkStyle);
    {
        QFile stylesheet(QDir::homePath() + "/PROJECTS/gui_core/styles/dark_style.css");
        if (stylesheet.open(QIODevice::ReadOnly))
            a.setStyleSheet(stylesheet.readAll());
    }
    Test w;
    w.show();
    return a.exec();
}
