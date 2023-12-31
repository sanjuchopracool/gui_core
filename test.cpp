#include "test.h"
#include <QIntValidator>
#include <QToolButton>
#include <QVBoxLayout>
#include "widgets/checkable_icon.h"
#include "widgets/editors/number_editor.h"
#include "widgets/linked_number_editor.h"

Test::Test(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout * main_layout = new QVBoxLayout();
    IntEditor * int_editor = new IntEditor(this);
    int_editor->set_range(0, 100);
    int_editor->set_value(78);
    int_editor->set_suffix("px");
    main_layout->addWidget(int_editor);

    DoubleEditor* double_editor = new DoubleEditor(this);
    double_editor->set_range(0, 100);
    double_editor->set_value(22.65);
    double_editor->set_suffix("%");
    main_layout->addWidget(double_editor);

    IntPairEditor *two_int_editor = new IntPairEditor(this);
    two_int_editor->set_suffix("px");
    two_int_editor->set_range(-100, 500);
    main_layout->addWidget(two_int_editor);

    DoublePairEditor *two_double_editor = new DoublePairEditor(this);
    two_double_editor->set_suffix("%");
    two_double_editor->set_range(-50.0, 100);
    main_layout->addWidget(two_double_editor);

    LinkedIntEditor *lint = new LinkedIntEditor(true, this);
    lint->set_range(-50, 133);
    lint->set_suffix("inch");
    main_layout->addWidget(lint);

    LinkedDoubleEditor *ldbl = new LinkedDoubleEditor(true, this);
    ldbl->set_range(-50.0123, 233.355);
    ldbl->set_suffix("m");
    main_layout->addWidget(ldbl);

    QToolButton *btn = new QToolButton(this);
    btn->setIcon(QIcon(":icons/dark/actions/16@2x/link.png"));
    main_layout->addWidget(btn);

    setLayout(main_layout);

    //    connect(qApp, &QApplication::focusChanged, this, [](QWidget *old, QWidget *now) {
    //        qDebug() << "old: " << old << " new: " << now;
    //    });

    setMinimumWidth(300);
}

Test::~Test()
{
}
