#ifndef SYSTEMPANEL_H
#define SYSTEMPANEL_H

#include "actorpanel.h"
#include <list>

#include <memory>

class SymSystem;
class SystemPanel;

class QVBoxLayout;

class QSplitter;
class QTabWidget;

class VectorEdit;

/* System panel declaration */

class SystemPanel : public ActorPanel
{
    Q_OBJECT

    SymSystem * system;

    std::list<SKViewerPanel*> nestedPanels;

    QVBoxLayout * centerLayout;

    /* Splitter between screen and values, vertical */
    QSplitter * screenSplitter;

    QTabWidget * actorScreen;
    QWidget * valuesWidget;

    /* Splitter between offset and dedicated, horizontal */
    QSplitter * valueSplitter;
    QVBoxLayout * centerValues;

    VectorEdit * offsetEdit;
    QWidget * dedicated;

private slots:

    void offsetChange(std::size_t, double);

protected:

    virtual void updatePlugin() {}

public:

    SystemPanel(SymSystem*, QWidget* parent = 0);
    ~SystemPanel();

    void setSystem(SymSystem*);

    SymSystem * getSystem();
    const SymSystem * getSystem() const;

    /* Screen panel modifiers */

    void pushToScreen(SKViewerPanel*);

    void clear();

    virtual QWidget * getDedicated() override;


    /* Override update */

    virtual void updatePanel() override;
};

#endif // SYSTEMPANEL_H
