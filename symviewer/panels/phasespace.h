#ifndef PHASESPACE_H
#define PHASESPACE_H

#include "plotpanel.h"

class Oscillateur;
class SKPlot2D;

struct PhaseSpaceFunction
{
    /* Oscillateur instance a' se referer */
    Oscillateur *oscillateur;

    /* Index of the freedom degrees */
    int index;
};

class QPushButton;
class QGroupBox;
class QLabel;

class PhaseSpace : public PlotPanel
{
    Q_OBJECT

    SKPlot2D * plot;
    std::vector<PhaseSpaceFunction> functions;

    QVBoxLayout * centering;
    QVBoxLayout * inside;

    QGroupBox * buttons;

    QPushButton * start;
    QPushButton * stop;
    QPushButton * clear;

    bool plotting;

    /* Commands panel */

    QGroupBox * commands;
    QVBoxLayout * commandsLayout;

    QLabel * com_ws, * com_hjkl;

private slots:

    void startPlotting();
    void stopPlotting();
    void clearPlotting();

public:

    PhaseSpace(const QString& title, float lineWidth = 1, QWidget *parent = 0);
    ~PhaseSpace();

    void addFunction(Oscillateur*, int index);

    virtual void updatePanel() override;
};

#endif // PHASESPACE_H
