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
