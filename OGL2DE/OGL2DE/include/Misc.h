#ifndef _MISC_H_
#define _MISC_H_

#include <cstdlib>
#include <algorithm>
#include "glew.h"
#include "glfw3.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace std;

namespace Justin
{
	//slightly modified by me
	struct Vertex {
		union {
			struct {
				glm::vec3 Pos;
				glm::vec4 Color;
				glm::vec2 UV;
			};
		
			struct {
				float X, Y, Z;
				float R, G, B, A;
				float U, V;
			};
		};
	};

	void glfw_window_size_callback(GLFWwindow* window, int width, int height);
	void glfw_error_callback(int error, const char * description);
	void glfw_update_fps_counter(GLFWwindow* window);
};

namespace Sam
{
	/* Globals */
	extern int iWindowWidth;
	extern int iWindowHeight;
	extern GLFWwindow * MyWindow;
	extern glm::mat4 Projection;

	/* Functions */
	GLuint LoadTexture(const char *, int, int);
	GLFWwindow* NewWindow();
	float Random();
	float RandRange( float fMin, float fMax );
	glm::vec3 RandUnitVec();

};

#endif













