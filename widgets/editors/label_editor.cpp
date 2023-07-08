#include "label_editor.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QMouseEvent>

void LabelEditor::enterEvent(QEnterEvent *ev)
{
    override_cursor();
    QLabel::enterEvent(ev);
}

void LabelEditor::leaveEvent(QEvent *ev)
{
    restore_cursor();
    QLabel::leaveEvent(ev);
}

void LabelEditor::mousePressEvent(QMouseEvent *ev)
{
    m_start_pos = ev->position();
    ev->accept();
}

void LabelEditor::mouseReleaseEvent(QMouseEvent *event)
{
    if (!m_move_started) {
        emit mouse_released();
    } else {
        emit mouse_move_end(event->position());
    }

    m_move_started = false;
    event->accept();
}

void LabelEditor::mouseMoveEvent(QMouseEvent *ev)
{
    if (!m_move_started) {
        m_move_started = true;
        emit mouse_move_started(ev->position());
    } else {
        emit mouse_moved(ev->position());
    }

    ev->accept();
}

void LabelEditor::override_cursor()
{
    QApplication::setOverrideCursor(QCursor(Qt::SizeHorCursor));
}

void LabelEditor::restore_cursor()
{
    QApplication::restoreOverrideCursor();
}

SuffixedLabelEditor::SuffixedLabelEditor(QWidget *parent)
    : QWidget{parent}
{
    m_text_label = new LabelEditor(this);
    m_text_label->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred));

    m_suffix_label = new QLabel(this);
    m_suffix_label->setSizePolicy(
        QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred));

    m_suffix_label->setBuddy(m_text_label);
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->addWidget(m_text_label);
    main_layout->addWidget(m_suffix_label);
    setLayout(main_layout);

    connect(m_text_label, &LabelEditor::mouse_released, this, &SuffixedLabelEditor::mouse_released);
    connect(m_text_label,
            &LabelEditor::mouse_move_started,
            this,
            &SuffixedLabelEditor::mouse_move_started);
    connect(m_text_label, &LabelEditor::mouse_moved, this, &SuffixedLabelEditor::mouse_moved);
    connect(m_text_label, &LabelEditor::mouse_move_end, this, &SuffixedLabelEditor::mouse_move_end);
}

void SuffixedLabelEditor::set_text(const QString &text)
{
    m_text_label->setText(text);
}

void SuffixedLabelEditor::set_suffix(const QString &text)
{
    m_suffix_label->setText(text);
}
