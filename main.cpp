#include <QApplication>
#include <QDir>
#include <QFile>
#include "styles/dark_style.h"
#include "test.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(icons);
    Q_INIT_RESOURCE(stylesheet);
    QApplication a(argc, argv);
    //    QIcon::setThemeSearchPaths(QStringList() << ":dark");
    QIcon::setThemeName(":dark");
    QApplication::setStyle(new DarkStyle);
    {
        QFile stylesheet(":styles/dark_style.css");
        if (stylesheet.open(QIODevice::ReadOnly))
            a.setStyleSheet(stylesheet.readAll());
    }
    Test w;
    w.show();
    return a.exec();
}
