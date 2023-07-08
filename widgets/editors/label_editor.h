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
    bool m_move_started = false;
};

class SuffixedLabelEditor : public QWidget
{
    Q_OBJECT
public:
    explicit SuffixedLabelEditor(QWidget *parent = nullptr);

signals:
    void mouse_released();
    void mouse_move_started(QPointF);
    void mouse_moved(QPointF);
    void mouse_move_end(QPointF);

public slots:
    void set_text(const QString &text);
    void set_suffix(const QString &text);

private:
    LabelEditor *m_text_label = nullptr;
    QLabel *m_suffix_label = nullptr;
};

#endif // LABELEDITOR_H
