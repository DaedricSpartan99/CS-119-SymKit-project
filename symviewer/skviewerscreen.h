#ifndef SKVIEWERSCREEN_H
#define SKVIEWERSCREEN_H

#include <QStackedWidget>
#include <list>

class SKViewerPanel;
class QStackedLayout;

class SKViewerScreen : public QStackedWidget
{
    Q_OBJECT

    std::list<SKViewerPanel*> panels;

    //std::vector<QWidget*> initPriorityList;
    bool initialized;

public:

    SKViewerScreen(QWidget *parent = 0);
    ~SKViewerScreen();

    /*
     * Update all panels
     */
    void updatePanels();

    void addViewerPanel(SKViewerPanel*);
    void rmViewerPanel(SKViewerPanel*, bool del = false);
    void clear(bool del = false);

    void setCurrentPanel(SKViewerPanel*);
    SKViewerPanel * getCurrentPanel();

    //void initializePriorities();

    //void addInitPriority(QWidget*);
};

#endif
