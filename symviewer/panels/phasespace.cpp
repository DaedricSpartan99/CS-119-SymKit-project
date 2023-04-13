#include "phasespace.h"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>

#include "descriptors/oscillateur.h"

#include "skplot2d.h"

#include <QLabel>

PhaseSpace::PhaseSpace(const QString &label, float lineWidth, QWidget *parent)
    : PlotPanel(new SKPlot2D(lineWidth), parent), plotting(false)
{
    plot = static_cast<SKPlot2D*>(getPlot());
    plot->setWindowTitle(label);

    centering = new QVBoxLayout;

    /* Buttons setup */

    buttons = new QGroupBox(tr("Phase space controlling"));

    centering->addWidget(buttons);

    inside = new QVBoxLayout;

    start = new QPushButton(tr("&Start"), buttons);
    stop = new QPushButton(tr("&Stop"), buttons);
    clear = new QPushButton(tr("&Clear"), buttons);

    inside->addWidget(start);
    inside->addWidget(stop);
    inside->addWidget(clear);

    buttons->setLayout(inside);

    connect(start, SIGNAL(clicked()), this, SLOT(startPlotting()));
    connect(stop, SIGNAL(clicked()), this, SLOT(stopPlotting()));
    connect(clear, SIGNAL(clicked()), this, SLOT(clearPlotting()));

    /* Commands instructions panel */

    commands = new QGroupBox("Commands");

    commandsLayout = new QVBoxLayout;

    com_ws = new QLabel("W/S: Zoom", commands);
    com_hjkl = new QLabel("H/J/K/L: Left, Down, Up, Right", commands);

    commandsLayout->addWidget(com_ws);
    commandsLayout->addWidget(com_hjkl);

    commands->setLayout(commandsLayout);

    centering->addWidget(commands);

    /* Add to dedicated */

    PlotPanel::addToDedicated(buttons);
    PlotPanel::addToDedicated(commands);

    centering->setStretch(0, 7);
    centering->setStretch(1, 3);

    PlotPanel::setDedicatedLayout(centering);
}

PhaseSpace::~PhaseSpace()
{
    delete plot;
    delete buttons;
}

void PhaseSpace::addFunction(Oscillateur *oscill, int index)
{
    PhaseSpaceFunction f = {oscill, index};
    functions.push_back(f);

    plot->registerNewStream();
}

void PhaseSpace::updatePanel()
{
    if (plotting)
    {

        for (size_t i = 0; i < functions.size(); ++i)
        {
            const PhaseSpaceFunction& f = functions[i];

            (*plot)[i] <<
                Point2D(f.oscillateur->getp()[f.index],
                f.oscillateur->getp_prime()[f.index]);
        }
    }

    if (plot->isVisible() || plot->isAxysUpdateScheduled())
        plot->updateGraph();
}

void PhaseSpace::startPlotting()
{
    plotting = true;
}

void PhaseSpace::stopPlotting()
{
    plotting = false;
}

void PhaseSpace::clearPlotting()
{
    plot->clearAll();
}
