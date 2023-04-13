#ifndef __SPECS_H__
#define __SPECS_H__

/* 8-bit type definition for shape flags */
typedef unsigned char specs_t;

#define S_EVOLVE        0x1    // first bit     00000001
#define S_RENDER        0x2    // second bit    00000010
#define S_FILL_MODE     0x4    // third bit     00000100
#define S_POSITION      0x8    // fourth bit    00001000
#define S_ORIENTATION   0x10   // fifth bit     00010000
#define S_SCALING       0x20   // sixth bit     00100000
#define S_COLOR         0x40   // seventh bit   01000000
#define S_DESCRIPTOR    0x80   // eighth bit    10000000

/*
 * define the variable to be added on the private or
 * protected side of a class declaration
*/
#define SPECS_VAR specs_flags

/*
 * Define abstractly the methods to be generated into
 * the public side a class declaration
 */
#define SPECS_METHODS(specs_Name, specs_bit)            \
                                                        \
    virtual bool is##specs_Name() const override        \
    {                                                   \
        return (SPECS_VAR & specs_bit) != 0;            \
    }                                                   \
                                                        \
    void toggle##specs_Name()                           \
    {                                                   \
        SPECS_VAR ^= specs_bit;                         \
    }                                                   \
                                                        \
    void set##specs_Name(bool value)                    \
    {                                                   \
        if (value)                                      \
            SPECS_VAR |= specs_bit;                     \
        else                                            \
            SPECS_VAR &= ~specs_bit;                    \
    }

/*
 * Define all generation methods
 */

// expand this macro into a class inheriting Evolvable
#define SPECS_EVOLVE SPECS_METHODS(Evolving, S_EVOLVE)

// expand this macro into a class inheriting Renderable
#define SPECS_RENDER SPECS_METHODS(Rendering, S_RENDER)

// expand this macro into a class inheriting Renderable
#define SPECS_FILL_MODE SPECS_METHODS(FillMode, S_FILL_MODE)

// expand this macro into a class inheriting Positionable
#define SPECS_POSITION SPECS_METHODS(Positioning, S_POSITION)

// expand this macro into a class inheriting Orientable
#define SPECS_ORIENTATION SPECS_METHODS(Orientating, S_ORIENTATION)

// expand this macro into a class inheriting Scalable
#define SPECS_SCALING SPECS_METHODS(Scaling, S_SCALING)

// expand this macro into a class inheriting Colorable
#define SPECS_COLOR SPECS_METHODS(Coloring, S_COLOR)

// expand this macro into a class inheriting Descriptable
#define SPECS_DESCRIPTOR SPECS_METHODS(RunningDescriptor, S_DESCRIPTOR)

/*
 * Field to be added inside the class in order to make
 * work all specs generated methods
 */
#define SPECS_FIELD specs_t SPECS_VAR;

/*
 * Accessors to set the specs flags in one time
 */
#define SPECS_ACCESS                                    \
                                                        \
    void setSpecs(specs_t value)                        \
    {                                                   \
        SPECS_VAR = value;                              \
    }                                                   \
                                                        \
    specs_t getSpecs() const                            \
    {                                                   \
        return SPECS_VAR;                               \
    }                                                   \
                                                        \
    void toggleSpecs(specs_t value)                     \
    {                                                   \
        SPECS_VAR ^= value;                             \
    }                                                   \
                                                        \
    void setSpecsState(specs_t value, bool state)       \
    {                                                   \
        if (state)                                      \
            SPECS_VAR |= value;                         \
        else                                            \
            SPECS_VAR &= ~value;                        \
    }

#endif // __SPECS_H__
