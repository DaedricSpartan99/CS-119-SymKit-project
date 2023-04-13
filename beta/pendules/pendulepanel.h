#ifndef PENDULEPANEL_H
#define PENDULEPANEL_H

#include "panels/actorpanel.h"

class PenduleS;
class Pendule;

class QSplitter;
class QVBoxLayout;

class QGridLayout;

class Valuedit;
class VectorEdit;

class PhaseSpace;

class PenduleSimplePanel : public ActorPanel
{
    Q_OBJECT

    Pendule * pendule;
    PenduleS * desc;

    QVBoxLayout * centering;
    QSplitter * splitter;

    PhaseSpace * plot;

    QWidget * valuepanel;

    QGridLayout * valuesLayout;

    Valuedit * angle;
    Valuedit * speed;

    Valuedit * length;
    Valuedit * mass;
    Valuedit * friction;
    Valuedit * gravity;

    VectorEdit * offset;

private slots:

    void angleChanged(double);
    void speedChanged(double);
    void lengthChanged(double);
    void massChanged(double);
    void frictionChanged(double);
    void gravityChanged(double);

    void offsetChanged(std::size_t, double);

public:

    PenduleSimplePanel(Pendule *, QWidget * parent = 0);
    ~PenduleSimplePanel();

    PhaseSpace * getPhaseSpace();

    virtual void updatePanel() override;
};

#endif // PENDULEPANEL_H
