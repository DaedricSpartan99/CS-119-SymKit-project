#ifndef VALUEDIT_H
#define VALUEDIT_H

class QLineEdit;
class QLabel;
class QHBoxLayout;

#include <QWidget>

class Valuedit : public QWidget
{
    Q_OBJECT

    QLabel * name;
    QLineEdit * edit;

    QHBoxLayout * layout;

signals:

    void valueChanged(double);

private slots:

    void returnHandler();

public:

    /* Passing a null pointer as value means to lock edit */
    Valuedit(const QString& name,
             double init = 0,
             QWidget *parent = 0);

    ~Valuedit();

    QString getName() const;

    void setValue(double, bool force = false);
    double getValue() const;

    bool isFocused() const;
};

#endif // VALUEDIT_H
