#include "valuevisual.h"

#include <QLabel>
#include <QHBoxLayout>

Valuevisual::Valuevisual(const QString& name, double init, QWidget *parent)
    : QWidget(parent)
{
    this->name = new QLabel(name, this);
    visual = new QLabel(QString::number(init, 'g', 4), this);

    this->name->setBuddy(visual);

    layout = new QHBoxLayout;

    layout->addWidget(this->name);
    layout->addWidget(visual);

    setLayout(layout);
}

Valuevisual::~Valuevisual()
{
    delete name;
    delete visual;
    delete layout;
}

QString Valuevisual::getName() const
{
    return name->text();
}

void Valuevisual::setValue(double value)
{
    visual->setText(QString::number(value, 'g', 4));
}

double Valuevisual::getValue() const
{
    return visual->text().toDouble();
}
