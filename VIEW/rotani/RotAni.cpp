#include "RotAni.h"

#include "../MainWindow.h"

RotAni::RotAni(MainWindow* pV)
: m_pV(pV),
  m_playing(false), m_playIndex(0),
  m_lastPlayTime(GetTime()),
  m_rotAngle(0.0), m_rotMethod(ROTATE_NONE)
{
}

RotAni::~RotAni()
{
}

CubeRotateMethod RotAni::getRotMethod()
{
    return m_rotMethod;
}

double RotAni::getRotAngle()
{
    return m_rotAngle;
}

// make the rotate animation smoothly
double RotAni::easingDelta(double currentAngle)
{
    if (currentAngle < 1e-5) {
        return ROTATE_SPEED * 180.0;
    }else {
        return ROTATE_SPEED * std::min(180.0, 8100.0 / currentAngle);
    }
}

void RotAni::rotateFinishCallback()
{
    if(m_rotMethod == ROTATE_NONE) return;

    m_pV->notifyAllObservers(m_rotMethod);

    m_rotAngle = 0.0;
    m_rotMethod = ROTATE_NONE;

    if (m_playing) playNext();
}

void RotAni::nextFrame()
{
    double currentTime = GetTime();

    if(m_rotMethod != ROTATE_NONE) {
        if(m_pV->m_pRenderer->getRenderState() == 0) // finish incomplete rotation
            m_pV->m_pRenderer->setRenderState(1);
        double dAngle = easingDelta(m_rotAngle) * (currentTime - m_lastPlayTime);
        m_rotAngle += dAngle;
        if (m_rotAngle >= 90.0) {
            rotateFinishCallback();
        }
    }

    m_lastPlayTime = currentTime;
}

void RotAni::finishCurrentRotate()
{
    m_rotAngle = 90.0;
    rotateFinishCallback();
}

void RotAni::startRotate(CubeRotateMethod method)
{
    // finish incomplete rotation
    if(m_rotMethod != ROTATE_NONE)
        finishCurrentRotate();
    // start new single rotation
    m_rotMethod = method;
    m_lastPlayTime = GetTime();
}

void RotAni::play()
{
    if(m_pV->m_pRSteps->size() <= 0) return;
    m_playIndex = 0;
    m_playing = true;
    startRotate(m_pV->m_pRSteps->at(m_playIndex));
}

void RotAni::playNext()
{
    if(!m_playing) return;

    if(++m_playIndex < (ptrdiff_t)(m_pV->m_pRSteps->size())) {
        startRotate(m_pV->m_pRSteps->at(m_playIndex));
    }else {
        stopPlay();
    }
}

void RotAni::stopPlay()
{
    m_playing = false;
    m_playIndex = 0;
    m_pV->m_pRenderer->setRenderState(1);
}