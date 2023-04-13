#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H

namespace symkit
{
    struct mouse_s;
}

class MouseListener
{

public:

    //methodes à définir dans un MouseListener pour la gestion des input clavier
    virtual void onMouseClick(const symkit::mouse_s&) = 0;

    virtual void onMouseRelease(const symkit::mouse_s&) = 0;

    virtual void onMouseMove(const symkit::mouse_s&) = 0;

    void enableMouseListener(bool value)
    {
        enabled = value;
    }

    bool isMouseListenerEnabled()
    {
        return enabled;
    }

private:

    bool enabled;
};

#endif // MOUSELISTENER_H
