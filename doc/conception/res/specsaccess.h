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
