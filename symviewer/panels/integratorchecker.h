#ifndef INTEGRATORCHECKER_H
#define INTEGRATORCHECKER_H

#include <QGroupBox>

class Oscillateur;

class QVBoxLayout;

class QRadioButton;

class SKActor;

class IntegratorChecker : public QGroupBox
{
    Q_OBJECT

    Oscillateur * desc;

    QVBoxLayout * layout;

    QRadioButton * euler_cromer;
    QRadioButton * newmark;

private slots:

    void switchToEulerCromer();
    void switchToNewmark();

public:

    IntegratorChecker(Oscillateur *, QWidget * parent = 0);
    ~IntegratorChecker();

    static Oscillateur * getOscillator(SKActor *);
};

#endif // INTEGRATORCHECKER_H
