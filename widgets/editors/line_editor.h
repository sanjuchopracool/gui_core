#ifndef LINEEDITOR_H
#define LINEEDITOR_H

#include <QLineEdit>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QValidator;
class QLabel;
QT_END_NAMESPACE

class LineEditor : public QLineEdit
{
    Q_OBJECT
public:
    LineEditor(QWidget *parent);

signals:
    void editing_ended();
    void up_key_pressed();
    void down_key_pressed();
    void editing_finished(const QString &str);

protected:
    void focusOutEvent(QFocusEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // LINEEDITOR_H
