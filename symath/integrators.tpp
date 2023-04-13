#ifdef __INTEGRATORS_TPP__

template<typename T>
void symkit::integrateEulerCromer(T& position, T& speed, const T& acceleration, float dt)
{
    speed += acceleration * dt;
    position += speed * dt;
}

template<typename T, class Owner>
void symkit::integrateNewmark(T& position, T& speed, equation_f<T, Owner> equation, Owner *owner, float dt, double error)
{
    T p0(position), p1(speed), s( (owner->*equation)() ), q, r;
    unsigned int timeout = MAX_NEWMARK_LOOPS;

    do{

        q=position;
        r= (owner->*equation)();

        speed = p1 +  (r+s)*dt/2.0;
        position = p0 + p1 * dt + ( r/2 + s )*dt*dt/3;

    } while( position - q >= error && timeout--);
}

#endif // __INTEGRATORS_TPP__
