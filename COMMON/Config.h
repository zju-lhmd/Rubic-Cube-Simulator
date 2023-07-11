#ifndef CONFIG_H
#define CONFIG_H

// App Default Configuration

// window width and height
#define WIDTH  (800)
#define HEIGHT (600)
// window background color
#define BACKGROUND_COLOR 1.0f, 0.95f, 0.92f, 1.0f
// view perspective
#define DEFAULT_VIEW_ANGLE_X (45.0)
#define DEFAULT_VIEW_ANGLE_Y (-45.0)
// rank of cube
// #define RANK (3)
// rgb color of cube faces
#define RGB_GRAY 0.5f, 0.5f, 0.5f
#define RGB_RED 1.0f, 0.0f, 0.0f
#define RGB_GREEN 0.0f, 1.0f, 0.0f
#define RGB_ORANGE 1.0f, 0.5f, 0.0f
#define RGB_BLUE 0.0f, 0.0f, 1.0f
#define RGB_YELLOW 1.0f, 1.0f, 0.0f
#define RGB_WHITE 1.0f, 1.0f, 1.0f
// rotate speed
#define ROTATE_SPEED (1.5)
// cube file length (3*3*3 sub cubes, each sub cube has 6 faces)
#define FORMAT_LENGTH (3 * 3 * 3 * 6)

#endif