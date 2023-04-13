#ifndef RESSORTPANEL_H
#define RESSORTPANEL_H

#include "panels/actorpanel.h"

class Ressort;
class Ressor;

class QVBoxLayout;

class PhaseSpace;

class QGridLayout;

class Valuedit;
class VectorEdit;

class RessortPanel : public ActorPanel
{
    Q_OBJECT

    Ressor * ressor;
    Ressort * desc;

    QVBoxLayout * centering;
    QSplitter * splitter;

    PhaseSpace * plot;

    QWidget * valuepanel;

    QGridLayout * valuesLayout;

    Valuedit * position;
    Valuedit * speed;
    VectorEdit * offset;

    Valuedit * k;
    Valuedit * mass;
    Valuedit * friction;
    Valuedit * length;
    Valuedit * gravity;

    VectorEdit * axys;

private slots:

    void positionChanged(double);
    void speedChanged(double);

    void offsetChanged(std::size_t, double);

    void kChanged(double);
    void massChanged(double);
    void frictionChanged(double);
    void lengthChanged(double);
    void gravityChanged(double);

    void axysChange(std::size_t, double);

public:

    RessortPanel(Ressor *, QWidget * parent = 0);
    ~RessortPanel();

    PhaseSpace * getPhaseSpace();

    virtual void updatePanel() override;
};

#endif // RESSORTPANEL_H
