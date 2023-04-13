#include "descriptorviewer.h"

DescriptorViewer::DescriptorViewer(Descriptor *desc)
    : descriptor(desc)
{

}

void DescriptorViewer::setDescriptor(Descriptor* desc)
{
    this->descriptor = desc;
}

const Descriptor * DescriptorViewer::getDescriptor() const
{
    return descriptor;
}
