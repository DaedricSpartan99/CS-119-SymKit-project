    /*
     * Generate specs accessor methods
     *
     * These methods allow to
     * access the SPECS_VAR by a "set" and a "get" method
     *
     * In particular, the set method allows to set all flags in one
     * using the numerical macros defined in "specs.h"
     * For example:
     *
     * setSpecs(S_EVOLVE | S_RENDER | S_POSITION | S_COLOR);
     */
    SPECS_ACCESS

protected:

    /*
     * Generate the specs flags field
     *
     * This macro is expanded to
     *
     * specs_t SPECS_VAR;
     *
     * This field must be protected in order to pass
     * the flags bit-wise structure to the children classes,
     * so they can generate the accessors methods defined
     * in "specs.h"
     */
    SPECS_FIELD
