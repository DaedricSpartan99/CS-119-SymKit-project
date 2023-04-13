#ifndef PLOTPANEL_H
#define PLOTPANEL_H

#include "skviewerpanel.h"

class SKPlot;
class QVBoxLayout;

class QSplitter;

class PlotPanel : public SKViewerPanel
{
    SKPlot * glwidget;
    QVBoxLayout * centering;

    QSplitter * splitter;

    QWidget * dedicated;

public:

    PlotPanel(SKPlot *, QWidget *parent = 0);
    ~PlotPanel();

    void setPlot(SKPlot *);

    SKPlot * getPlot();

    virtual QString getLabel() const override;

    virtual QWidget * getDedicated() override;
};

#endif // PLOTPANEL_H
