#include "skviewerscreen.h"

#include <QStackedLayout>
#include "skviewerpanel.h"

SKViewerScreen::SKViewerScreen(QWidget *parent)

    : QStackedWidget(parent), initialized(false)
{
}

SKViewerScreen::~SKViewerScreen()
{
}

/*void SKViewerScreen::initializePriorities()
{
    if (initialized)
        return;

    for (auto p : initPriorityList)
    {
        p->repaint();
    }

    initialized = true;
}

void SKViewerScreen::addInitPriority(QWidget *widget)
{
    initPriorityList.push_back(widget);
}*/

void SKViewerScreen::updatePanels()
{
    /* Update recursively all panels */
    for (auto panel : panels)
        panel->updatePanel();
}

void SKViewerScreen::addViewerPanel(SKViewerPanel* panel)
{
    // give this as parent reference
    panel->setParent(this);

    // add panel to the layout
    addWidget(panel);

    // add panel to the update list
    panels.push_back(panel);
}

void SKViewerScreen::rmViewerPanel(SKViewerPanel* panel, bool del)
{
    // remove parent reference
    panel->setParent(0);

    // remove from layout reference
    removeWidget(panel);

    // remove from update list
    panels.remove(panel);

    /*
     * Warning, this may cause segmentation faults if bad used
     * That's why it is not applicated by default
     */
    if (del)
        delete panel;
}

void SKViewerScreen::clear(bool del)
{
    for (auto panel : panels)
    {
        panel->setParent(0);

        removeWidget(panel);

        if (del)
            delete panel;
    }

    panels.clear();
}

void SKViewerScreen::setCurrentPanel(SKViewerPanel *panel)
{
    setCurrentWidget(panel);
}

SKViewerPanel * SKViewerScreen::getCurrentPanel()
{
    return static_cast<SKViewerPanel*>(currentWidget());
}
