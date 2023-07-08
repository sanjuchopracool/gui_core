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

    QString path = QDir::homePath() + "/PROJECTS/gui_core/icons/dark";
    qDebug() << QIcon::themeSearchPaths();
    QIcon::setThemeSearchPaths(QStringList() << path);
    QIcon::setThemeName("dark");
    qDebug() << QIcon::hasThemeIcon("link");

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
