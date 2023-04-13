#ifndef ACTORPANEL_H
#define ACTORPANEL_H

#include "skviewerpanel.h"

class SKActor;
class SpecsChecker;

class QSplitter;
class QBoxLayout;

class QVBoxLayout;

class IntegratorChecker;

class ActorPanel : public SKViewerPanel
{
    Q_OBJECT

    SKActor * actor;

    QSplitter * splitter;
    QBoxLayout * centering;

    QWidget * dedicated;

    QWidget * checkerContainer;
    QVBoxLayout * checkerLayout;
    QSplitter * checkerSplitter;

    SpecsChecker * checker;

    /*
     * It activates only if the actor object is
     * describable and the descriptor is an oscillateur
     */
    IntegratorChecker * integrators;

protected:

    QWidget * actorPanelDedicated();

public:

    ActorPanel(SKActor * actor, QWidget *parent = 0);
    ~ActorPanel();

    void setActor(SKActor * actor);

    SKActor * getActor();
    const SKActor * getActor() const;

    SpecsChecker * getChecker();
    const SpecsChecker * getChecker() const;

    virtual QString getLabel() const override;

    virtual QWidget * getDedicated() override;

public slots:

    void setEvolvingState(bool);
    void setRenderingState(bool);

    void setPositioningState(bool);
    void setOrientingState(bool);
    void setScalingState(bool);

    void setColoringState(bool);

    void setDescribingState(bool);
};

#endif // ACTORPANEL_H
