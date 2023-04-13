#ifndef PENDULERESSORTPANEL_H
#define PENDULERESSORTPANEL_H

#include "panels/systempanel.h"

class RessortSphere;

class PenduleRessort;

class Valuedit;
class QGridLayout;

class PendrSphere;

class PendSpherePanel : public ActorPanel
{
    Q_OBJECT

    PenduleRessort * descriptor;

    Valuedit * angle;
    Valuedit * speed;
    Valuedit * length;
    Valuedit * mass;
    Valuedit * friction;
    Valuedit * gravity;

    QGridLayout * layout;

private slots:

    void angleChanged(double);
    void speedChanged(double);
    void lengthChanged(double);
    void frictionChanged(double);
    void massChanged(double);
    void gravityChange(double);

public:

    PendSpherePanel(PendrSphere*, PenduleRessort *descriptor, QWidget *parent = 0);
    ~PendSpherePanel();

    virtual void updatePanel() override;
};

class RessortSpherePanel : public ActorPanel
{
    Q_OBJECT

    PenduleRessort * descriptor;

    Valuedit * position;
    Valuedit * speed;
    Valuedit * k;
    Valuedit * mass;
    Valuedit * friction;

    QGridLayout * layout;

private slots:

    void positionChanged(double);
    void speedChanged(double);
    void kChanged(double);
    void massChanged(double);
    void frictionChanged(double);

public:

    RessortSpherePanel(PendrSphere*, PenduleRessort *descriptor, QWidget *parent = 0);
    ~RessortSpherePanel();

    virtual void updatePanel() override;
};

class PenduleR;
class Valuevisual;
class QHBoxLayout;
class PhaseSpace;


class PenduleRessortPanel : public SystemPanel
{
    Q_OBJECT

    PenduleR * pend_ressort;
    PenduleRessort * desc;

    QHBoxLayout * layout;

    Valuevisual * energy;

    PendSpherePanel * pendule;
    RessortSpherePanel * ressort;

    PhaseSpace * plot;

    virtual void updatePlugin() override;

public:

    PenduleRessortPanel(PenduleR*, QWidget *parent = 0);
    ~PenduleRessortPanel();

    PhaseSpace * getPhaseSpace();

};

#endif // PENDULERESSORTPANEL_H
