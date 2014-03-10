#ifndef _QUAD_H_
#define _QUAD_H_

#include "Misc.h"
#include "ShaderProgram.h"
#include "Texture.h"



using namespace Sam;

/*
	Quad Class
		
		OpenGL Quad Primitive Class, all OpenGL specific function calls are performed within this class and not
		the sprite class. This is done to allow for portability in the event of a different API design (most likely
		Direct X) ...
*/

class Quad 
{
	public:

		Quad(const char * a_TexFilepath, int a_iWidth, int a_iHeight, int a_iFrameWidth, int a_FrameHeight); // My Textures are Sprite Sheets with Square Dimensions
		~Quad();

		void SetUVOffset(float u, float v); //For manipulating UV Coordinates within Sprite Sheet (Animation).
		void SetUVOffset(glm::vec2 uv);

		void Draw();
		void LoadTexture(const char * a_TexFilepath);

	protected:

		/* Standard members */
		int m_iTextureWidth; //Actual Texture (Sprite Sheet) Dimensions in pixels
		int m_iTextureHeight;
		int m_iQuadWidth; //Primitive Dimensions in pixels
		int m_iQuadHeight;
		unsigned int m_uiTexture; // The texture loaded in with SOIL
		unsigned int m_uiSourceBlendMode;
		unsigned int m_uiDestinationBlendMode;

		Justin::Vertex m_aoVertices[4]; // Array of Vertices, see "Vertex" Structure in Misc.h
		glm::mat4 m_Model; //Culumnating affine  transformation matrix (Translation * Rotation * Scale)
		glm::mat4 m_View;  //Camera Matrix, not currently in use
		glm::vec2 m_v2UVOffset; //Texture coordinate offset for Sprite Sheet use later
		glm::vec2 m_v2FrameDimensions; //Size of each frame in pixel dimensions (75 x 75 etc)
		glm::vec2 m_v2FrameDimensionsNorm; // Dimensions of each "frame" in the texture expressed in normalized device coordinates
		
		/* OpenGL members */

		ShaderProgram * m_ShaderProgram;
		Texture * m_Texture;
		GLuint m_VBO; // Vertex Buffer Object
		GLuint m_EBO; // Element Buffer Object
		GLuint m_VAO; // Vertex Attribute Object
		
		/* Shader IDs */
		GLint m_MatrixID; // Location of MVP Matrix in Vertex Shader
		GLint m_TextureID; // Location of Texture in Vertex Shader
		GLint m_UVOffsetID; // Location of UV Offset in Vertex Shader
		
		

};
#endif