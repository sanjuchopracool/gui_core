#ifndef TEST_H
#define TEST_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Test; }
QT_END_NAMESPACE

class Test : public QWidget
{
    Q_OBJECT

public:
    Test(QWidget *parent = nullptr);
    ~Test();

private:
    Ui::Test *ui;
};
#endif // TEST_H
