#include <iostream>
#include "Player.h"
#include "Window.h"

Window::Window() : m_bInitialized(false)
{

}

Window::~Window()
{

}

int Window::Initialize(int a_iWidth = 1024, int a_iHeight = 768, char * a_pTitle = "Default Title")
{

	m_bInitialized = true;
	m_iWidth = a_iWidth;
	m_iHeight = a_iHeight; 

	if( !glfwInit() )
	{
		std::cout << "Failed to initialized GLFW.\n";
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 16);
	//Fullscreen mode stuff

	m_oContext = glfwCreateWindow(m_iWidth, m_iHeight, "OGL2DE", NULL, NULL);
	glfwSetWindowSize(m_oContext, m_iWidth, m_iHeight);
	glfwMakeContextCurrent(m_oContext);

	if(!m_oContext)
	{
		std::cout << "ERROR: Could not open GLFW3 Window\n" ;
		glfwTerminate();
	}

	glewExperimental = GL_TRUE;
	glewInit();

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);

	std::cout << ("Renderer: %s\n", renderer);
	std::cout << ("OpenGL Version: %s\n", version);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LESS);
	glEnable(GL_CULL_FACE);

	std::cout << "\nGLFW Context Initialized successfully.\n\n" ;

	Tester = new Player();

	return 0;
}


void Window::Update()
{
		/* Render loop*/
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, .5);
		glEnable(GL_ALPHA);
		glViewport(0, 0, m_iWidth, m_iHeight);

		Tester->Input();
		Tester->Draw();

		glfwPollEvents();
		glfwSwapBuffers(m_oContext);

		glClearColor(0.0f, 0.25f, 1.0f, 1.0f);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Close()
{
	glfwTerminate();
}