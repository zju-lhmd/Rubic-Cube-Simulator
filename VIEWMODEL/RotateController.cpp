#include "RotateController.h"

RotateController::RotateController()
    : playing(false), stepsToPlay(),
      playIndex(0),
      lastPlayTime(glfwGetTime()),
      rotateAngle(0.0), finishAngle(90.0),
      rotateMethod(ROTATE_NONE)
{
}

RotateController::~RotateController()
{
}

void RotateController::SetCube(Cube* pCube)
{
    cube = pCube;
}

cubes_t RotateController::GetCubeData()
{
    return cube->GetCubes();
}

CubeRotateMethod RotateController::GetRotateMethod()
{
    return rotateMethod;
}
double RotateController::GetRotateAngle()
{
    return rotateAngle;
}

double RotateController::easingDelta(double currentAngle)
{
    currentAngle = std::abs(currentAngle);
    if (currentAngle == 0.0) {
        return ROTATE_SPEED * 180.0;
    }else {
        return ROTATE_SPEED * std::min(180.0, 8100.0 / currentAngle);
    }
}

void RotateController::rotateFinishCallback()
{
    if(rotateMethod == ROTATE_NONE) return;

    cube->DoMethod(rotateMethod);

    rotateAngle = 0.0;
    rotateMethod = ROTATE_NONE;

    if (playing) playNext();
}

void RotateController::nextFrame()
{
    double currentTime = glfwGetTime();

    if(rotateMethod != ROTATE_NONE) {
        double delta = easingDelta(rotateAngle) * (currentTime - lastPlayTime);
        rotateAngle += delta;
        if (rotateAngle >= finishAngle) {
            rotateFinishCallback();
        }
    }

    lastPlayTime = currentTime;
}

void RotateController::finishCurrentRotate()
{
    rotateAngle = finishAngle;
    rotateFinishCallback();
}

void RotateController::startRotate(CubeRotateMethod method)
{
    if(rotateMethod != ROTATE_NONE)
        finishCurrentRotate();
    rotateMethod = method;
    lastPlayTime = glfwGetTime();
}

void RotateController::play(CubeSteps &steps)
{
    if(steps.size() <= 0) return;
    stepsToPlay = steps;
    playIndex = 0;
    playing = true;
    startRotate(stepsToPlay[0]);
}

void RotateController::playNext()
{
    if(!playing) return;

    ++playIndex;
    if(playIndex < (ptrdiff_t)stepsToPlay.size()) {
        startRotate(stepsToPlay[playIndex]);
    }else {
        stopPlay();
    }
}

void RotateController::stopPlay()
{
    playing = false;
    playIndex = 0;
}