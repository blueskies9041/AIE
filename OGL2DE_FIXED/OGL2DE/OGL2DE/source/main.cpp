/*
	PROJECT INFORMATION

		Name: SamOGL
		Brief: Beginnings of Samuel Legus's AIE Assessment 4 Project

		* Significant Changes:
			MOTHER FUCKING TEXT

		* To Do
			Make something like a game.
			Particles!

				
	LAST RECORDED EDITS ON: March 04, 2014
*/

#include "glew.h"
#include "glfw3.h"
#include "Player.h"
#include <iostream>
#include "Text.h"
#include "Timer.h"
#include "Window.h"

using namespace std;

void main()
{
	/* Test Objects */

	Timer::GetInstance();
	Window::GetInstance().Initialize(1024, 768, "HELLO");
	
	//Text T("resources/graphics/Holstein.png");
	//Text Z("resources/graphics/Holstein2.png");	

	//Sprite SpriteA("resources/graphics/ZeroSpriteSheet.png", 200, 200, 75, 75, Window::GetInstance().GetContext());
	//Player Player1(Window::GetInstance().GetContext());

	
	//SpriteA.m_v3Position.x += 150.0f;

	/* Main Loop */

	while (!glfwWindowShouldClose(Window::GetInstance().GetContext()))
	{	
		if (glfwGetKey(Window::GetInstance().GetContext(), GLFW_KEY_Q))
			glfwSetWindowShouldClose(Window::GetInstance().GetContext() , 1);

		/* Draw Calls */
		//T.Print("Text.", 10, 100, 25);
		//Z.Print("Text. NOW WITH BLUE H AND BLACKNESS! ", 10, 165, 25);
		
	/*	SpriteA.Draw();
		Player1.Input();
		Player1.Draw();*/

		Window::GetInstance().Update();
    }

	Window::GetInstance().Close();
}

