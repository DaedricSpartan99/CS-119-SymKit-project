#include "valuedit.h"
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>

Valuedit::Valuedit(const QString& name,
                   double init,
             QWidget *parent)

    : QWidget(parent)
{
    this->name = new QLabel(name, this);
    edit = new QLineEdit(this);
    edit->setText(QString::number(init));
    this->name->setBuddy(edit);

    layout = new QHBoxLayout;

    layout->addWidget(this->name);
    layout->addWidget(edit);

    setLayout(layout);

    connect(edit, SIGNAL(returnPressed()), this, SLOT(returnHandler()));
}

Valuedit::~Valuedit()
{
    delete name;
    delete edit;
    delete layout;
}

void Valuedit::returnHandler()
{
    // remove focus
    edit->clearFocus();

    emit valueChanged(getValue());
}

QString Valuedit::getName() const
{
    return name->text();
}

void Valuedit::setValue(double value, bool force)
{
    if (force || !isFocused())
        edit->setText(QString::number(value, 'g', 4));
}

double Valuedit::getValue() const
{
    return edit->text().toDouble();
}

bool Valuedit::isFocused() const
{
    return edit->hasFocus();
}
