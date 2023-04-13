#ifndef VALUEVISUAL_H
#define VALUEVISUAL_H

class QLabel;
class QHBoxLayout;

#include <QWidget>

class Valuevisual : public QWidget
{
    QLabel * name;
    QLabel * visual;

    QHBoxLayout * layout;

public:

    Valuevisual(const QString& name,
                double init = 0,
                QWidget *parent = 0);

    ~Valuevisual();

    QString getName() const;

    void setValue(double value);

    double getValue() const;
};

#endif // VALUEVISUAL_H
