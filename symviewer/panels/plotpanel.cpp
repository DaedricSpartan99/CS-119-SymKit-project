#include "plotpanel.h"

#include "skplot.h"
#include <QVBoxLayout>
#include <QSplitter>

#include "skerror.h"

using namespace symkit;

PlotPanel::PlotPanel(SKPlot *plot, QWidget *parent)

    : SKViewerPanel(parent), glwidget(plot)
{
    splitter = new QSplitter;
    centering = new QVBoxLayout;

    centering->addWidget(splitter);

    dedicated = new QWidget;

    if (!plot)
        throw SKError(ERR_NULL_POINTER, "PlotPanel::PlotPanel", "PlotPanel", "Passing a null pointer as plot");

    splitter->addWidget(plot);
    splitter->addWidget(dedicated);

    splitter->setStretchFactor(0, 9);
    splitter->setStretchFactor(1, 1);
    splitter->setCollapsible(1, true);

    setLayout(centering);
}

PlotPanel::~PlotPanel()
{
    delete centering;
}

void PlotPanel::setPlot(SKPlot *plot)
{
    if (plot)
    {
        if (glwidget)
        {
            glwidget->setParent(0);
        }

        splitter->insertWidget(0, plot);

        glwidget = plot;
    }
}

SKPlot * PlotPanel::getPlot()
{
    return glwidget;
}

QString PlotPanel::getLabel() const
{
    return glwidget->windowTitle();
}

QWidget * PlotPanel::getDedicated()
{
    return dedicated;
}
