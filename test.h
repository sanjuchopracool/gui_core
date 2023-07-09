#ifndef TEST_H
#define TEST_H

#include <QWidget>

class Test : public QWidget
{
    Q_OBJECT

public:
    Test(QWidget *parent = nullptr);
    ~Test();
};
#endif // TEST_H
