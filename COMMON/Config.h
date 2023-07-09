#ifndef CONFIG_H
#define CONFIG_H

// App default configuration
// window width and height
#define WIDTH  (800)
#define HEIGHT (600)
// window background color
#define BACKGROUND_COLOR 1.0f, 0.95f, 0.87, 1.0f
// view perspective
#define DEFAULT_VIEW_ANGLE_X (45.0)
#define DEFAULT_VIEW_ANGLE_Y (-45.0)
// rotate animation speed
#define ROTATE_SPEED (1.5)
// rubic cube file length (3*3*3 sub cubes, each sub cube has 6 faces)
#define FORMAT_LENGTH (3 * 3 * 3 * 6)

#endif