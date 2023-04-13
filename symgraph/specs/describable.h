#ifndef DESCRIPTABLE_H
#define DESCRIPTABLE_H

#include <iosfwd>

class Descriptor;

class Describable
{

public:

    // give a descriptor specification inheriting this class
    Describable(Descriptor* desc = 0);

    virtual ~Describable();

    void bind(Descriptor *);

    void release();

    bool isBound() const;

    Descriptor * getDescriptor();

    const Descriptor * getDescriptor() const;

    /*
     * Evolution method
     * Check for bound state before calling
     * this function !
     */
    void updateDescriptor(float dt);

    /* virtual state check method */
    virtual bool isRunningDescriptor() const = 0;

protected:

    /*
     * Warning!
     * This method is not type safe, use with consciousness
     */
    template<class T>
    T * cast_descriptor()
    {
        return static_cast<T*>(descriptor);
    }

    template<class T>
    const T * cast_descriptor() const
    {
        return static_cast<T*>(descriptor);
    }

private:

    Descriptor * descriptor;
};

std::ostream& operator<<(std::ostream& out, const Describable& d);

#endif
