class Evolvable
{
public:

    virtual ~Evolvable() {}

    virtual void evolve(float dt) = 0;

    virtual bool isEvolving() const = 0;
};
