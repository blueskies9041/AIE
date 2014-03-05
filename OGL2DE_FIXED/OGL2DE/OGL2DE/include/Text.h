#ifndef _TEXT_H_
#define _TEXT_H_

#include "Misc.h"
#include <vector>

class Text
{
	public:

		Text(const char * a_pTextureFilepath); // Primary Constructor : Handles Shaders, Buffers, and Texture
		~Text();

		void LoadTexture(const char* a_TexFilepath);  // SOIL texture load, loads texture into texture object, also sets the 2D Texture uniform in the fragment shader
		void Print(const char * a_cpText, int a_XPos, int a_YPos, int a_iSize); // " Draw " Call, outputs text (of [sizedimensions) at specified X/Y Position
		
	protected:

		//Standard Data
		std::vector<glm::vec2> m_Vertices; // Vertex Positions
		std::vector<glm::vec2> m_UVs; // UV Coordinates

		int m_iTextureWidth; // Size of Font Atlas
		int m_iTextureHeight; 

		GLuint m_VAO;
		GLuint m_VertexBuffer;
		GLuint m_UVBuffer;
		GLuint m_ShaderProgram;

		unsigned int m_uiTexture; //Texture loaded through Soil

		//GLSL Uniforms
		GLuint m_ScreenDimensionsID; //Uniform for screen resizing
		GLuint m_TextureID; //Uniform in fragment shader

};


#endif