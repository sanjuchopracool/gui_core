#include "test.h"
#include <QIntValidator>
#include <QToolButton>
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

    ui->two_int_editor->set_suffix("px");
    ui->two_int_editor->set_range(-100, 500);

    ui->two_double_editor->set_suffix("%");
    ui->two_double_editor->set_range(-50.0, 100);
    QToolButton *btn = new QToolButton(this);
    btn->setIcon(QIcon::fromTheme("link"));
    ui->verticalLayout->addWidget(btn);

    btn = new QToolButton(this);
    btn->setIcon(QIcon(":icons/dark/actions/16@2x/link.png"));
    ui->verticalLayout->addWidget(btn);

    //    connect(qApp, &QApplication::focusChanged, this, [](QWidget *old, QWidget *now) {
    //        qDebug() << "old: " << old << " new: " << now;
    //    });

    setMinimumWidth(300);
}

Test::~Test()
{
    delete ui;
}
