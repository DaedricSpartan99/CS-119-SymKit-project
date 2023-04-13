class AnActor : public SKActor, public Evolvable
{
    /* Update from Evolvable */
    virtual void update(float) override;

    /* Methodes pour acceder et modifier la flag de S_EVOLVE */
    SPECS_EVOLVE
}
