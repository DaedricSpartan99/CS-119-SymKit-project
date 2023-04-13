#include "skviewer.h"

#include <QListWidget>
#include <QVBoxLayout>
#include <QSplitter>
#include "skviewerpanel.h"

#include "skviewerscreen.h"

#include "consoleviewer.h"
#include <iostream>

#include "skplot2d.h"

SKViewer::SKViewer(const QString& title) : QMainWindow()
{
    setWindowTitle(title);

    resize(800, 700);

    windowSplitter = new QSplitter(Qt::Vertical, this);
    panelSplitter = new QSplitter;

    screenContainer = new QWidget;
    screenContainerLayout = new QVBoxLayout;

    chooser = new QListWidget;
    screen = new SKViewerScreen;

    panelSplitter->addWidget(chooser);
    panelSplitter->addWidget(screen);

    screenContainerLayout->addWidget(panelSplitter);
    screenContainer->setLayout(screenContainerLayout);

    panelSplitter->setStretchFactor(0, 4);
    panelSplitter->setStretchFactor(1, 7);

    windowSplitter->addWidget(screenContainer);

    // empty widget
    windowSplitter->addWidget(new QWidget);

    windowSplitter->setStretchFactor(0, 24);
    windowSplitter->setStretchFactor(1, 1);

    windowSplitter->setCollapsible(1, true);

    connect(chooser, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(chooseHandler(QListWidgetItem*)));

    setCentralWidget(windowSplitter);
}

#include <iostream>

using namespace std;

SKViewer::~SKViewer()
{
    delete windowSplitter;
}

void SKViewer::addViewerPanel(SKViewerPanel *panel)
{
    if (!panel)
    {
        // TODO, throw error
    }

    screen->addViewerPanel(panel);
    chooser->addItem(panel->getLabel());
}

void SKViewer::removeViewerPanel(SKViewerPanel *panel, bool del)
{
    int index = screen->indexOf(panel);

    if (index == -1)
        return;

    if (index == screen->currentIndex() && index > 0)
        screen->setCurrentIndex(index - 1);

    QListWidgetItem * itemWidget = chooser->item(index);

    chooser->removeItemWidget(itemWidget);
    screen->rmViewerPanel(panel, del);
}

void SKViewer::clear(bool del)
{
    chooser->clear();
    screen->clear(del);
}

void SKViewer::chooseHandler(QListWidgetItem *clicked)
{
    int row = chooser->row(clicked);

    if (row == -1)
        return;

    screen->setCurrentIndex(row);
}

void SKViewer::updatePanels()
{
    screen->updatePanels();

    // refresh panel
    screen->update();
}
