#ifndef PENDCOUPLEPANEL_H
#define PENDCOUPLEPANEL_H

#include "panels/systempanel.h"

class PendSphere;
class Valuedit;

class QGridLayout;
class PenduleDesc;

class PenduleSpherePanel : public ActorPanel
{
    Q_OBJECT

    PenduleDesc * descriptor;
    int index;

    Valuedit * angle;
    Valuedit * speed;
    Valuedit * length;
    Valuedit * mass;

    QGridLayout * layout;

private slots:

    void angleChanged(double);
    void speedChanged(double);
    void lengthChanged(double);
    void massChanged(double);

public:

    PenduleSpherePanel(PendSphere*, PenduleDesc *descriptor, int index, QWidget *parent = 0);
    ~PenduleSpherePanel();

    virtual void updatePanel() override;
};

class PenduleCouple;
class Valuevisual;
class QHBoxLayout;
class PhaseSpace;

class PenduleCouplePanel : public SystemPanel
{
    Q_OBJECT

    PenduleCouple * pendule;
    PenduleDesc * desc;

    QHBoxLayout * layout;

    Valuedit * gravity;
    Valuevisual * energy;

    PenduleSpherePanel * spheres[2];

    PhaseSpace * plot;

    virtual void updatePlugin() override;

private slots:

    void gravityChange(double);

public:

    PenduleCouplePanel(PenduleCouple*, QWidget *parent = 0);
    ~PenduleCouplePanel();

    PhaseSpace * getPhaseSpace();
};

#endif // PENDCOUPLEPANEL_H
