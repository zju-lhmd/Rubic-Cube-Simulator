#ifndef ROTANI_H
#define ROTANI_H

#include "../../COMMON/config.h"
#include "../../COMMON/types.h"
#include "../../COMMON/utilities.h"

class MainWindow;

class RotAni {
public:
    RotAni(MainWindow* pV);

    ~RotAni();

    CubeRotateMethod getRotMethod();
    double getRotAngle();

    double easingDelta(double);
    void rotateFinishCallback();
    void nextFrame();
    void finishCurrentRotate();
    void startRotate(CubeRotateMethod);
    void play();
    void playNext();
    void stopPlay();
private:
    MainWindow* m_pV;

    bool m_playing = false;
    ptrdiff_t m_playIndex = 0;
    double m_lastPlayTime;

    double m_rotAngle;
    CubeRotateMethod m_rotMethod;
};


#endif