#include "Misc.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include "Assert.h"
#include "GLLOG.h"
#include "SOIL.h"


using namespace std;

namespace Justin
{
	void glfw_window_size_callback(GLFWwindow* window, int width, int height)
	{
		Sam::iWindowWidth = width;
		Sam::iWindowHeight = height;
	}
	void glfw_error_callback(int error, const char * description)
	{
		fputs(description, stderr);
		gl_log(description, __FILE__, __LINE__);
		//update matrices below
	}
	void glfw_update_fps_counter(GLFWwindow* window)
	{
		static double previous_seconds = glfwGetTime();
		static int frame_count;
		double current_seconds = glfwGetTime();
		double elapsed_seconds = current_seconds - previous_seconds;
		if(elapsed_seconds > .25)
		{
			previous_seconds = current_seconds;
			double fps = (double)frame_count / elapsed_seconds;
			char tmp[128];
			sprintf(tmp, "OpenGL @ FPS %.2f", fps);
			glfwSetWindowTitle(window, tmp);
			frame_count = 0;
		}
		frame_count++;
	}
};

namespace Sam
{
	/* Globals */
	int iWindowWidth = 1024;
	int iWindowHeight = 768;

	float fDeltaTime = 0.0f;
	glm::mat4 Projection = glm::ortho( 0.0f,			    // Left
									  (float)iWindowWidth,  //Right
									  (float)iWindowHeight, //Top
									   0.0f,			    //Bottom
									   0.0f,			    //Near
									  -1.0f);			    //Far

	//Projection matrix creates normal computer coordinate system.
	//Origin (0,0) at top left and (Window Width, Window Height) at bottom right
	
	/* Functions */
	glm::mat4 m4Projection = glm::ortho(0.0f,1024.0f,768.0f,0.0f,0.0f,100.0f);
	glm::mat4 m4View = glm::mat4(1.0f);

	GLFWwindow* MyWindow = Sam::NewWindow();
	GLFWwindow* NewWindow()
	{
		glfwInit();

		char message[256];
		sprintf(message, "Starting GLFW %s\n", glfwGetVersionString());
		assert(gl_log(message, __FILE__, __LINE__));
		glfwSetErrorCallback(Justin::glfw_error_callback);

		glfwWindowHint(GLFW_SAMPLES, 16);
		//Fullscreen mode stuff
		GLFWmonitor* mon = glfwGetPrimaryMonitor();

		const GLFWvidmode* vmode = glfwGetVideoMode(mon);
		GLFWwindow* MyWindow = glfwCreateWindow(vmode ->width, vmode->height, "FUCK YYEAAAHHHHH AUSTRALIA", NULL, NULL);

		glfwSetWindowSize(MyWindow, iWindowWidth, iWindowHeight);
		glfwMakeContextCurrent(MyWindow);

		if(!MyWindow)
		{
			fprintf( stderr, "ERROR: Could not open GLFW3 Window\n");
			glfwTerminate();
		}

		glfwMakeContextCurrent(MyWindow);

		glewExperimental = GL_TRUE;
		glewInit();

		const GLubyte* renderer = glGetString(GL_RENDERER);
		const GLubyte* version = glGetString(GL_VERSION);
		printf ("Renderer: %s\n", renderer);
		printf( "OpenGL Version: %s\n\n", version);

		glEnable (GL_DEPTH_TEST);
		glDepthFunc (GL_LESS);

		return MyWindow;
		}
	GLuint LoadTexture(const char * a_cpFilepath, int a_iWidth, int a_iHeight) {

		GLuint TextureID = 0;
		unsigned char* cpImage = SOIL_load_image(a_cpFilepath, &a_iWidth, &a_iHeight, 0, SOIL_LOAD_RGBA);
		glBindTexture( GL_TEXTURE_2D, TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, a_iWidth, a_iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, cpImage);
		SOIL_free_image_data(cpImage);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		return TextureID;
	}
	float Random()
	{
		return rand() / (float)RAND_MAX;
	}
	float RandRange( float fMin, float fMax )
	{
		if ( fMin > fMax ) std::swap( fMin, fMax );
		return ( Random() * ( fMax - fMin ) ) +fMin;
	}
	glm::vec3 RandUnitVec()
	{
		float x = ( Random() * 2.0f ) - 1.0f;
		float y = ( Random() * 2.0f ) - 1.0f;
		float z = ( Random() * 2.0f ) - 1.0f;

		return glm::normalize( glm::vec3(x,y,z) );
	}

};


