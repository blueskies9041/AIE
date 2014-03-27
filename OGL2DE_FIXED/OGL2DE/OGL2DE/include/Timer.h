#ifndef _TIMER_H_
#define _TIMER_H_

#include "Misc.h"

class Timer 
{
	private:

		float m_fDeltaTime;
		float m_fTotalTime;

	public:

		Timer();
		~Timer();
		void Update();

		inline static Timer& GetInstance() {static Timer oInstance; return oInstance;}
		inline float GetDeltaTime() { return m_fDeltaTime; }
		inline float GetTotalTime() { return m_fTotalTime; }
};

#endif