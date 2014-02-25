/*
	PROJECT INFORMATION

		Name: SamOGL
		Brief: Beginnings of Samuel Legus's AIE Assessment 4 Project

		* Significant Changes:
			Redid everything.

		* To Do:
				Animated Sprite Class
					Animation XMl FIle
					Sprite Sheet (coordinate) XML File

		

	LAST RECORDED EDITS ON: Feb 24, 2014
*/

#include "glew.h"
#include "glfw3.h"
#include "Sprite.h"
#include "Particle.h"
#include <iostream>
#include "tinyxml2.h"

using namespace std;
/* */

void main()
{
	/* Test Sprite Object */

	CSprite * Sprite = new CSprite("resources/graphics/ZeroSpriteSheet.png", 100, 100, 900, 1200, 75, 75, MyWindow);


	/* Main Loop */
	while (!glfwWindowShouldClose(MyWindow))
	{	
        /* Render loop*/
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, .5);
		glEnable(GL_ALPHA);
		glViewport(0,0,Sam::iWindowWidth, Sam::iWindowHeight);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Sprite->Input();
		Sprite->Draw();

		/* DEBUGGING */
		if(glfwGetTime() >= 5) {
			glfwSetTime(0);
			//cout << "("<< Sprite->m_v3Position.x << "," << Sprite->m_v3Position.y << ")" << endl;
		}

        glfwSwapBuffers(MyWindow);

        /* Poll for and process events */
		if(GLFW_PRESS == glfwGetKey(MyWindow, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(MyWindow, true);
		
		Justin::glfw_update_fps_counter(MyWindow);

		glfwPollEvents();
    }

	Sprite->Cleanup();
	delete Sprite;
	glfwTerminate();
}

