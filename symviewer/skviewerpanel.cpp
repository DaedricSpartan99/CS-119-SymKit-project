#include "skviewerpanel.h"

#include <QLayout>

SKViewerPanel::SKViewerPanel(QWidget *parent)

    : QWidget(parent)
{

}

void SKViewerPanel::addToDedicated(QWidget *widget)
{
    widget->setParent(getDedicated());

    QLayout * layout = getDedicated()->layout();

    if (layout)
        layout->addWidget(widget);
}

void SKViewerPanel::removeFromDedicated(QWidget *widget)
{
    widget->setParent(0);

    QLayout * layout = getDedicated()->layout();

    if (layout)
        layout->removeWidget(widget);
}

void SKViewerPanel::setDedicatedLayout(QLayout *layout)
{
    getDedicated()->setLayout(layout);
}
