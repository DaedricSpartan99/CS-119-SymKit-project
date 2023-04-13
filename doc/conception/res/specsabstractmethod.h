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
