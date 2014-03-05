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

using namespace std;

void main()
{
	
	ResetDeltaTime();

	/* Test Objects */

	Text T("resources/graphics/Holstein.png");
	Text Z("resources/graphics/Holstein2.png");	
	Sprite SpriteA("resources/graphics/ZeroSpriteSheet.png", 200, 200, 75, 75, g_MyWindow);
	Player Player1;
	
	SpriteA.m_v3Position.x += 150.0f;

	/* Main Loop */
	while (!glfwWindowShouldClose(g_MyWindow))
	{	

        /* Render loop*/
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, .5);
		glEnable(GL_ALPHA);
		glViewport(0,0,Sam::g_iWindowWidth, Sam::g_iWindowHeight);
		glClearColor(0.0f, 0.25f, 1.0f, 1.0f);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Draw Calls */
		T.Print("Hello.", 100, 100, 60);
		Z.Print("Hi.", 100, 500, 60);
		SpriteA.Draw();
		Player1.Input();
		Player1.Draw();

        glfwSwapBuffers(g_MyWindow);

        /* Poll for and process events */
		if(GLFW_PRESS == glfwGetKey(g_MyWindow, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(g_MyWindow, true);
		
		Justin::glfw_update_fps_counter(g_MyWindow);

		ResetDeltaTime();
		glfwPollEvents();
    }

	
	glfwTerminate();
}

