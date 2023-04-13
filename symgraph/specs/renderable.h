#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

namespace symkit
{
    struct render_s;
}

class Renderable
{

public:

    virtual ~Renderable() {}

    //foction qui définira la façon de dessinner un renderable
    virtual void render(symkit::render_s) = 0;

    virtual bool isRendering() const = 0;

    virtual bool isFillMode() const = 0;
};

#endif
