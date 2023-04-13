#ifndef OSCILLATEURPANEL_H
#define OSCILLATEURPANEL_H

#include "skviewerpanel.h"

class Descriptor;

class DescriptorViewer : public SKViewerPanel
{

    Descriptor * descriptor;

    // TODO graphical components for data printing


public:

    DescriptorViewer(Descriptor*);

    //virtual void update() override;

    void setDescriptor(Descriptor*);

    const Descriptor * getDescriptor() const;
};

#endif // OSCILLATEURPANEL_H
