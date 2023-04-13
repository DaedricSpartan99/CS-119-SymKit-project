#ifndef KEYLISTENER_H
#define KEYLISTENER_H

class KeyListener
{

public:

    /* Constructor and Destructor */
    KeyListener(bool enabled = true) : enabled(enabled) {}

    virtual ~KeyListener() {}

    //methodes à définir dans un KeyListener pour la gestion des input clavier
    virtual void onKeyPress(int key) = 0;

    virtual void onKeyRelease(int key) = 0;

    void enableKeyListener(bool value)
    {
        enabled = value;
    }

    bool isKeyListenerEnabled()
    {
        return enabled;
    }

private:

    bool enabled;
};

#endif // KEYLISTENER_H
