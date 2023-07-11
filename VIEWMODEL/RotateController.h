#ifndef ROTATECONTROLLER_H
#define ROTATECONTROLLER_H

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "../COMMON/Config.h" // common
#include "../MODEL/Cube.h" // model

class RotateController {
public:
    RotateController();

    ~RotateController();

    void SetCube(Cube* cube);
    cubes_t GetCubeData();

    CubeRotateMethod GetRotateMethod();
    double GetRotateAngle();

    double easingDelta(double);
    void rotateFinishCallback();
    void nextFrame();
    void finishCurrentRotate();
    void startRotate(CubeRotateMethod);
    void play(CubeSteps&);
    void playNext();
    void stopPlay();
private:
    // reference
    Cube* cube;

    bool playing = false;
    CubeSteps stepsToPlay;
    ptrdiff_t playIndex = 0;

    double lastPlayTime;
    double rotateAngle = 0.0, finishAngle = 90.0;
    CubeRotateMethod rotateMethod = ROTATE_NONE;
};


#endif