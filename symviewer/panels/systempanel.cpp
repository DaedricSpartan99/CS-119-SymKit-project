#include "systempanel.h"

#include <QVBoxLayout>
#include <QTabWidget>
#include "actors/systems/symsystem.h"
#include "skactor.h"
#include "actors/systems/symsystem.h"

#include <QSplitter>

#include "edit/vectoredit.h"

using namespace std;

/* SystemPanel section */

SystemPanel::SystemPanel(SymSystem *system, QWidget *parent)
    : ActorPanel(system, parent)
{
    /* set splitter as central widget */

    centerLayout = new QVBoxLayout;

    screenSplitter = new QSplitter;
    screenSplitter->setOrientation(Qt::Vertical);

    centerLayout->addWidget(screenSplitter);

    /* Add splitter to parent dedicated */

    QWidget * oldDedicated = actorPanelDedicated();

    screenSplitter->setParent(oldDedicated);

    oldDedicated->setLayout(centerLayout);

    /* add actor screen */

    actorScreen = new QTabWidget;

    screenSplitter->addWidget(actorScreen);

    /* add values widget */

    valuesWidget = new QWidget;

    screenSplitter->addWidget(valuesWidget);

    /* values widget layout setup */

    centerValues = new QVBoxLayout;

    valueSplitter = new QSplitter(valuesWidget);

    centerValues->addWidget(valueSplitter);
    valuesWidget->setLayout(centerValues);

    /* offset and dedicated */

    dedicated = new QWidget;

    offsetEdit = new VectorEdit("System offset",
                                Qt::Horizontal,
                                system->getOffset().rawdata(),
                                system->getOffset().size(),
                                dedicated);


    valueSplitter->addWidget(offsetEdit);
    valueSplitter->addWidget(dedicated);

    /* stretch factors */

    // set 85% spacing for screen
    screenSplitter->setStretchFactor(0, 85);

    // set 15% spacing for values
    screenSplitter->setStretchFactor(1, 15);

    // set 30% spacing for offset edit
    valueSplitter->setStretchFactor(0, 3);

    // set 70% spacing for dedicated
    valueSplitter->setStretchFactor(1, 7);

    setSystem(system);

    connect(offsetEdit,
            SIGNAL(valueChanged(std::size_t,double)),
            this,
            SLOT(offsetChange(std::size_t,double)));
}

SystemPanel::~SystemPanel()
{
    delete centerLayout;
    delete screenSplitter;
    /*delete valueSplitter;
    delete valuesWidget;
    delete actorScreen;
    delete offsetEdit;
    delete dedicated;*/
}

void SystemPanel::offsetChange(size_t index, double value)
{
    SVector<3> offset = system->getOffset();
    offset[index] = value;

    system->setOffset(offset);
}

void SystemPanel::setSystem(SymSystem *system)
{
    offsetEdit->setAll(system->getOffset().rawdata(), 3, true);

    this->system = system;
}

void SystemPanel::clear()
{
    actorScreen->clear();
    nestedPanels.clear();
}

SymSystem * SystemPanel::getSystem()
{
    return system;
}

const SymSystem * SystemPanel::getSystem() const
{
    return system;
}

QWidget * SystemPanel::getDedicated()
{
    return dedicated;
}

void SystemPanel::pushToScreen(SKViewerPanel *panel)
{
    nestedPanels.push_back(panel);

    actorScreen->addTab(panel, panel->getLabel());
}

void SystemPanel::updatePanel()
{
    for (auto panel : nestedPanels)
        panel->updatePanel();

    /* Call to plugin */
    updatePlugin();
}
