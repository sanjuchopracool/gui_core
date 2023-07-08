#include "dark_style.h"

#include <QStyleFactory>

DarkStyle::DarkStyle()
    : QProxyStyle(QStyleFactory::create("fusion"))
{}
