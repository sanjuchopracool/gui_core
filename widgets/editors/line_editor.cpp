#include "line_editor.h"

#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>

LineEdit::LineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    connect(this, &QLineEdit::editingFinished, this, [=]() { emit editing_finished(text()); });
    connect(this, &QLineEdit::editingFinished, this, &LineEdit::editing_ended);
}

void LineEdit::focusOutEvent(QFocusEvent *event)
{
    emit editing_ended();
    event->accept();
}

void LineEdit::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if (key == Qt::Key_Escape) {
        emit editing_ended();
        event->accept();
    } else if (key == Qt::Key_Up) {
        emit up_key_pressed();
        event->accept();
    } else if (key == Qt::Key_Down) {
        emit down_key_pressed();
        event->accept();
    } else {
        QLineEdit::keyPressEvent(event);
    }
}

LineEditor::LineEditor(QWidget *parent)
    : QWidget{parent}
{
    m_line_edit = new LineEdit(this);
    m_line_edit->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred));

    m_suffix_label = new QLabel(this);
    m_suffix_label->setSizePolicy(
        QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred));

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->addWidget(m_line_edit);
    main_layout->addWidget(m_suffix_label);
    setLayout(main_layout);

    m_suffix_label->setBuddy(m_line_edit);
    setFocusPolicy(Qt::StrongFocus);
    connect(m_line_edit, &LineEdit::editing_ended, this, &LineEditor::editing_ended);
    connect(m_line_edit, &LineEdit::up_key_pressed, this, &LineEditor::up_key_pressed);
    connect(m_line_edit, &LineEdit::down_key_pressed, this, &LineEditor::down_key_pressed);
    connect(m_line_edit, &LineEdit::editing_finished, this, &LineEditor::editing_finished);
}

void LineEditor::set_text(const QString &text)
{
    m_line_edit->setText(text);
}

void LineEditor::set_suffix(const QString &text)
{
    m_suffix_label->setText(text);
}

void LineEditor::focusInEvent(QFocusEvent *event)
{
    m_line_edit->setFocus();
}
