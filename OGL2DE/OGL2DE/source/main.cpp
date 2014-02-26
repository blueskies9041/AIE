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

using namespace std;
/* */

void main()
{
	/* Test Sprite Object */
	ResetDeltaTime();
	//Sprite * Sprite = new Sprite("resources/graphics/ZeroSpriteSheet.png", 100, 100, 900, 1200, 75, 75, MyWindow);
	Player Player;

	/* Main Loop */
	while (!glfwWindowShouldClose(MyWindow))
	{	

        /* Render loop*/
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, .5);
		glEnable(GL_ALPHA);
		glViewport(0,0,Sam::iWindowWidth, Sam::iWindowHeight);
		glClearColor(0.0f, 0.25f, 1.0f, 1.0f);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Player.Input();
		Player.Draw();

		/* DEBUGGING */
		//cout << fDeltaTime << endl;
		cout << glfwGetTime() * 1000.0f << endl;
        glfwSwapBuffers(MyWindow);

        /* Poll for and process events */
		if(GLFW_PRESS == glfwGetKey(MyWindow, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(MyWindow, true);
		
		Justin::glfw_update_fps_counter(MyWindow);

		ResetDeltaTime();
		glfwPollEvents();
    }

	
	glfwTerminate();
}

