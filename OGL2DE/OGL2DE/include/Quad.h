#ifndef _QUAD_H_
#define _QUAD_H_

#include "Misc.h"
#include "Shader.h"

using namespace Sam;

/*
	Quad Class
		
		OpenGL Quad Primitive Class, all OpenGL specific function calls are performed within this class and not
		the sprite class. This is done to allow for portability in the event of a different API design (most likely
		Direct X) ...
*/

class CQuad 
{
	public:

		CQuad(const char * a_TexFilepath, int a_iWidth, int a_iHeight, int a_iTextureWidth, int a_iTextureHeight, int a_iFrameWidth, int a_FrameHeight);
		~CQuad();

		void SetUVOffset(float u, float v); 
		void Update();

	protected:

		/* Standard members */
		int m_iTextureWidth;
		int m_iTextureHeight;
		int m_iQuadWidth;
		int m_iQuadHeight;

		Justin::Vertex m_aoVertices[4]; // Array of Vertices, see "Vertex" Structure in Misc.h
		glm::mat4 m_Model; //Culumnating affine  transformation matrix (Translation * Rotation * Scale)
		glm::mat4 m_View;  //Camera Matrix, not currently in use
		glm::vec2 m_v2UVOffset; //Texture coordinate offset for Sprite Sheet use later
		glm::vec2 m_v2FrameDimensions; //Size of each frame in pixel dimensions (75 x 75 etc)
		glm::vec2 m_v2UVUnit; // (Size of each "frame" in the texture expressed in normalized device (UV) coordinates
		
		/* OpenGL members */
		GLuint m_glShaderProgram;
		GLuint m_glVBO; // Vertex Buffer Object
		GLuint m_glEBO; // Element Buffer Object
		GLuint m_glVAO; // Vertex Attribute Object
		GLuint m_glTexture; // The texture loaded in with SOIL

		/* Shader IDs */
		GLuint m_glMatrixID; // Location of MVP Matrix in Vertex Shader
		GLint  m_glTextureID; // Location of Texture in Vertex Shader
		GLuint m_glUVOffsetID; // Location of UV Offset in Vertex Shader
		
		

};
#endif