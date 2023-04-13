#ifndef GLSPHERE_H
#define GLSPHERE_H

#include "glmodel.h"

namespace models
{
    //model graphique d'une sphère
    class GLSphere : public GLModel
    {
        GLuint slices, stacks;

    public:

        GLSphere(GLuint slices = 25, GLuint stacks = 25);
        GLSphere(const GLSphere&);

        virtual void initialize() override;
    };
}

#endif // GLSPHERE_H
