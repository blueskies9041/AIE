#include "Timer.h"

Timer::Timer() : m_fTotalTime(0.0f)
{
	glfwSetTime(0.0f);
}

Timer::~Timer()
{

}

void Timer::Update()
{
	float fCurrentTime = glfwGetTime();
	m_fDeltaTime = fCurrentTime - m_fTotalTime;
	m_fTotalTime = fCurrentTime;
}

