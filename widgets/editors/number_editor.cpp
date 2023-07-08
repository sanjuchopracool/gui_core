#include "number_editor.h"
#include <QApplication>
#include <QFocusEvent>
#include <QHBoxLayout>
#include <QStackedWidget>
#include "label_editor.h"
#include "line_editor.h"

enum EditMode { eLabel, eLineEdit };
NumberEditor::NumberEditor(QWidget *parent)
    : QWidget{parent}
{
    m_stack_widget = new QStackedWidget(this);
    m_stack_widget->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred));

    m_label_edit = new SuffixedLabelEditor(this);
    m_label_edit->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred));

    m_line_edit = new LineEditor(this);
    //    m_line_edit->installEventFilter(this);

    m_stack_widget->addWidget(m_label_edit);
    m_stack_widget->addWidget(m_line_edit);

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->addWidget(m_stack_widget);
    setLayout(main_layout);

    connect(m_label_edit,
            &SuffixedLabelEditor::mouse_released,
            this,
            &NumberEditor::enable_line_edit);
    connect(m_label_edit, &SuffixedLabelEditor::mouse_move_started, this, [this](const QPointF &pos) {
        m_prev_pos = pos;
        m_label_edit->set_text(text_value());
    });

    connect(m_label_edit, &SuffixedLabelEditor::mouse_moved, this, [this](const QPointF &pos) {
        calculate_delta(pos);
        m_label_edit->set_text(text_value());
    });

    connect(m_label_edit, &SuffixedLabelEditor::mouse_move_end, this, [this](const QPointF &pos) {
        calculate_delta(pos);
        m_label_edit->set_text(text_value());
    });

    connect(m_line_edit, &LineEditor::editing_ended, this, &NumberEditor::enable_label_edit);
    connect(m_line_edit, &LineEditor::up_key_pressed, this, [this]() {
        increase();
        m_line_edit->set_text(text_value());
    });
    connect(m_line_edit, &LineEditor::down_key_pressed, this, [this]() {
        decrease();
        m_line_edit->set_text(text_value());
    });
    connect(m_line_edit, &LineEditor::editing_finished, this, [this](const QString &str) {
        set_value_from_text(str);
    });

    setFocusPolicy(Qt::StrongFocus);
}

void NumberEditor::set_suffix(const QString &suffix)
{
    m_label_edit->set_suffix(suffix);
    m_line_edit->set_suffix(suffix);
}

void NumberEditor::set_text(const QString &text)
{
    m_label_edit->set_text(text);
    m_line_edit->set_text(text);
}

void NumberEditor::focusInEvent(QFocusEvent *event)
{
    m_stack_widget->currentWidget()->setFocus();
    event->accept();
}

void NumberEditor::enable_line_edit()
{
    m_line_edit->set_text(text_value());
    m_stack_widget->setCurrentIndex(eLineEdit);
}

void NumberEditor::enable_label_edit()
{
    m_label_edit->set_text(text_value());
    m_stack_widget->setCurrentIndex(eLabel);
}

void NumberEditor::calculate_delta(const QPointF &pos)
{
    m_delta = pos.x() - m_prev_pos.x() - (pos.y() - m_prev_pos.y());
    m_prev_pos = pos;
    emit delta_changed(m_delta);
}

IntEditor::IntEditor(QWidget *parent)
    : NumberEditor(parent)
{
    connect(this, &NumberEditor::delta_changed, this, [=](qreal delta) {
        m_value = validated_value(m_value + delta);
    });

    set_text(QString::number(m_value));
}

void IntEditor::set_range(int min, int max)
{
    Q_ASSERT(max > min);
    m_min = min;
    m_max = max;
}

void IntEditor::set_value(int value)
{
    m_value = validated_value(value);
    set_text(text_value());
}

QString IntEditor::text_value() const
{
    return QString::number(m_value);
}

void IntEditor::increase()
{
    m_value = validated_value(m_value + 1);
}

void IntEditor::decrease()
{
    m_value = validated_value(m_value - 1);
}

void IntEditor::set_value_from_text(const QString &text)
{
    bool ok = false;
    int value = text.toInt(&ok);
    if (ok) {
        m_value = validated_value(value);
    }
}

int IntEditor::validated_value(int value) const
{
    if (value < m_min)
        return m_min;
    if (value > m_max)
        return m_max;

    return value;
}

DoubleEditor::DoubleEditor(QWidget *parent)
    : NumberEditor(parent)
{
    connect(this, &NumberEditor::delta_changed, this, [=](qreal delta) {
        m_value = validated_value(m_value + delta);
    });

    set_text(QString::number(m_value));
}

void DoubleEditor::set_range(double min, double max)
{
    Q_ASSERT(max > min);
    m_min = min;
    m_max = max;
}

void DoubleEditor::set_value(double value)
{
    m_value = validated_value(value);
    set_text(text_value());
}

QString DoubleEditor::text_value() const
{
    return QString::number(m_value);
}

void DoubleEditor::increase()
{
    m_value = validated_value(m_value + 1);
}

void DoubleEditor::decrease()
{
    m_value = validated_value(m_value - 1);
}

void DoubleEditor::set_value_from_text(const QString &text)
{
    bool ok = false;
    double value = text.toDouble(&ok);
    if (ok) {
        m_value = validated_value(value);
    }
}

double DoubleEditor::validated_value(double value) const
{
    if (value < m_min)
        return m_min;
    if (value > m_max)
        return m_max;

    return value;
}
