#ifndef GLMARBLED_H
#define GLMARBLED_H

#include "glmodel.h"

namespace models
{
    //model graphique du sol
    class GLMarbled : public GLModel
    {

        GLuint stacks;

    public:

        GLMarbled(GLuint stacks = 16);
        GLMarbled(const GLMarbled&);

        virtual void initialize() override;
    };
}

#endif // GLMARBLED_H
