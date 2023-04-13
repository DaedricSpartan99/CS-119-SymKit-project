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
