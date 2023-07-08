#include "label_editor.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QMouseEvent>

void LabelEditor::enterEvent(QEnterEvent *ev)
{
    override_cursor();
    ev->accept();
}

void LabelEditor::leaveEvent(QEvent *ev)
{
    restore_cursor();
    ev->accept();
}

void LabelEditor::mousePressEvent(QMouseEvent *ev)
{
    m_start_pos = ev->position();
    m_move_pressed = true;
    emit mouse_move_started(ev->position());
    ev->accept();
}

void LabelEditor::mouseReleaseEvent(QMouseEvent *event)
{
    if (!m_move_started) {
        emit mouse_released();
    } else {
        emit mouse_move_end(event->position());
    }

    m_move_pressed = false;
    m_move_started = false;
    event->accept();
}

void LabelEditor::mouseMoveEvent(QMouseEvent *ev)
{
    if (m_move_pressed) {
        if (!m_move_started) {
            m_move_started = true;
        } else {
            emit mouse_moved(ev->position());
        }

        ev->accept();
    } else {
        QLabel::mouseMoveEvent(ev);
    }
}

void LabelEditor::override_cursor()
{
    QApplication::setOverrideCursor(QCursor(Qt::SizeHorCursor));
}

void LabelEditor::restore_cursor()
{
    QApplication::restoreOverrideCursor();
}
