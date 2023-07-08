#ifndef LABELEDITOR_H
#define LABELEDITOR_H

#include <QLabel>

class LabelEditor : public QLabel
{
    Q_OBJECT
public:
    LabelEditor(QWidget *parent)
        : QLabel(parent)
    {}

signals:
    void mouse_released();
    void mouse_move_started(QPointF);
    void mouse_moved(QPointF);
    void mouse_move_end(QPointF);

protected:
    void enterEvent(QEnterEvent *ev) override;
    void leaveEvent(QEvent *ev) override;

    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *ev) override;

private:
    void override_cursor();
    void restore_cursor();

private:
    QPointF m_start_pos;
    bool m_move_pressed = false;
    bool m_move_started = false;
};

#endif // LABELEDITOR_H
