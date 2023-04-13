#include "vectoredit.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

using namespace std;

void VectorEdit::returnHandle()
{
    size_t count(0);

    for (auto& c : components)
    {
        QLineEdit * edit = &(*c);

        // detect focused widget
        if (edit->hasFocus())
        {
            edit->clearFocus();
            emit valueChanged(count, getContent(count));
            break;
        }

        ++count;
    }
}

VectorEdit::VectorEdit(const QString &label, Qt::Orientation orient, const double * buffer, std::size_t size, QWidget *parent)
    : QGroupBox(label, parent)
{

    switch (orient)
    {
    case Qt::Vertical:
        layout = new QVBoxLayout;
        break;

    case Qt::Horizontal:
        layout = new QHBoxLayout;
        break;

    default:
        // TODO, error
        break;
    }

    setLayout(layout);

    if (buffer)
    {
        components.reserve(size);

        for (size_t i = 0; i < size; ++i)
            pushComponent(buffer[i]);
    }
}

VectorEdit::~VectorEdit()
{
}

std::size_t VectorEdit::pushComponent(double init)
{
    QLineEdit * edit = new QLineEdit(QString::number(init, 'g', 2), this);
    layout->addWidget(edit);

    connect(edit, SIGNAL(returnPressed()), this, SLOT(returnHandle()));

    components.push_back(unique_ptr<QLineEdit>(edit));

    QGroupBox::update();

    return components.size() - 1;
}

void VectorEdit::popComponent()
{
    layout->removeWidget(&(*components.back()));
    components.pop_back();

    QGroupBox::update();
}

std::size_t VectorEdit::size() const
{
    return components.size();
}

void VectorEdit::setContent(std::size_t index, double value, bool force)
{
    if (force || !isFocused(index))
        (*components[index]).setText(QString::number(value, 'g', 2));
}

double VectorEdit::getContent(std::size_t index)
{
    return (*components[index]).text().toDouble();
}

bool VectorEdit::isFocused(std::size_t index) const
{
    return (*components[index]).hasFocus();
}

void VectorEdit::setAll(const double *buffer, std::size_t count, bool force)
{
    if (count > size())
    {
        components.reserve(count);

        for (size_t i = count; i < count; ++i)
            pushComponent();
    }

    for (size_t i = 0; i < count; ++i)
    {
        if(force || ((*components[i]).hasFocus()))
            setContent(i, buffer[i]);
    }
}
