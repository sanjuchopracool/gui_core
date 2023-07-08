#ifndef LINEEDITOR_H
#define LINEEDITOR_H

#include <QLineEdit>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QValidator;
class QLabel;
QT_END_NAMESPACE

class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    LineEdit(QWidget *parent);

signals:
    void editing_ended();
    void up_key_pressed();
    void down_key_pressed();
    void editing_finished(const QString &str);

protected:
    void focusOutEvent(QFocusEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

class LineEditor : public QWidget
{
    Q_OBJECT
public:
    explicit LineEditor(QWidget *parent = nullptr);

signals:
    void editing_ended();
    void up_key_pressed();
    void down_key_pressed();
    void editing_finished(const QString &str);

public slots:
    void set_text(const QString &text);
    void set_suffix(const QString &text);

protected:
    void focusInEvent(QFocusEvent *event) override;

private:
    LineEdit *m_line_edit = nullptr;
    QLabel *m_suffix_label = nullptr;
};

#endif // LINEEDITOR_H
