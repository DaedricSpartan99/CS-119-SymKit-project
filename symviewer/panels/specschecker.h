#ifndef SPECSCHECKER_H
#define SPECSCHECKER_H

#include <QGroupBox>
#include "specs/specs.h"

class QVBoxLayout;
class SKActor;
class QLabel;

#include <QCheckBox>

class SpecsBox : public QCheckBox
{
    Q_OBJECT

    SKActor * actor;
    specs_t flag;

private slots:

    void toggleSpecs(bool);

public:

    SpecsBox(const QString&, SKActor *, specs_t flag, QWidget *parent = 0);

    specs_t getFlag() const;
};

#include <vector>

class SpecsChecker : public QGroupBox
{
    QVBoxLayout * layout;
    SKActor * actor;

    std::vector<SpecsBox*> boxes;

    SpecsBox * registerBox(specs_t);

public:

    SpecsChecker(SKActor * actor, QWidget * parent = 0);
    ~SpecsChecker();

    void setActor(SKActor*, bool reset = true);

    SKActor * getActor();
    const SKActor * getActor() const;

    SpecsBox * getByFlag(specs_t);
};

#endif // SPECSCHECKER_H
