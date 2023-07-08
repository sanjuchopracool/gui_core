#include "test.h"
#include <QIntValidator>
#include "./ui_test.h"

Test::Test(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Test)
{
    ui->setupUi(this);
    ui->intEditor->set_range(0, 100);
    ui->intEditor->set_value(78);
    ui->intEditor->set_suffix("px");

    ui->double_editor->set_range(0, 100);
    ui->double_editor->set_value(22.65);
    ui->double_editor->set_suffix("%");
    //    ui->lineEdit->setValidator(new QIntValidator(0, 100, this));
    //    connect(qApp, &QApplication::focusChanged, this, [](QWidget *old, QWidget *now) {
    //        qDebug() << "old: " << old << " new: " << now;
    //    });
}

Test::~Test()
{
    delete ui;
}
