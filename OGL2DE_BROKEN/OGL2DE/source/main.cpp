/*
	PROJECT INFORMATION

		Name: SamOGL
		Brief: Beginnings of Samuel Legus's AIE Assessment 4 Project

		* Significant Changes:
			Animations implemeneted.

		* To Do:
			Improve Movement
			Add minimal physics (gravity)
			Add particle system demo (projectile weapon + collision detection)
			Consider Constant Game Speed Loop vs DeltaTime based loop
				
	LAST RECORDED EDITS ON: Feb 25, 2014
*/

#include "glew.h"
#include "glfw3.h"
#include "Player.h"
#include <iostream>
#include "tinyxml2.h"
#include "Text2D.h"

using namespace std;
/* */

void main()
{
	/* Test Sprite Object */
	ResetDeltaTime();
	//Sprite * oSprite = new Sprite("resources/graphics/ZeroSpriteSheet.png", 100, 100, 900, 1200, 75, 75, g_MyWindow);

	Text T;
	T.Init("resources/graphics/Holstein.png", 1024, 1024);

	//Player Player1;

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


		T.Print("Sammy is Da Best Hello", 100, 100, 30);

		//Player1.Input();
		//Player1.Draw();

//		oSprite->Input();
		//oSprite->Draw();

		/* DEBUGGING */
        glfwSwapBuffers(g_MyWindow);

        /* Poll for and process events */
		if(GLFW_PRESS == glfwGetKey(g_MyWindow, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(g_MyWindow, true);
		
		Justin::glfw_update_fps_counter(g_MyWindow);

		ResetDeltaTime();
		glfwPollEvents();
    }

	//oSprite->Cleanup();

	//Player1.Cleanup();
	T.Cleanup();
	
	glfwTerminate();
}

