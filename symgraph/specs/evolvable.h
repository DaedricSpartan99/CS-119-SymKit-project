#ifndef EVOLVABLE_H
#define EVOLVABLE_H

class Evolvable
{
public:

    virtual ~Evolvable() {}

    virtual void evolve(float dt) = 0;

    virtual bool isEvolving() const = 0;
};

#endif // EVOLVABLE_H
