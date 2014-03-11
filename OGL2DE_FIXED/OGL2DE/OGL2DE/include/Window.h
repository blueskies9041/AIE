#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Misc.h"
#include "Player.h"

class Window
{
	private:

		Window();
		~Window();
		bool m_bInitialized;
		
		int m_iWidth;
		int m_iHeight;
		
	public:

		GLFWwindow * m_oContext;

		int Initialize(int a_iWidth, int a_iHeight , char * a_pTitle);
		void Update();
		void Close();

		Player * Tester;

		inline GLFWwindow * GetContext() { return m_oContext; }
		inline int GetWidth() { return m_iWidth; }
		inline int GetHeight() { return m_iHeight; }
		inline static Window& GetInstance() { static Window oInstance; return oInstance; }
		
};


#endif