#ifndef _TEXT2D_H_
#define _TEXT2D_H_

#include "Misc.h"
#include <vector>

class Text
{
	public:

		void Init(const char * a_cpTexturePath, int a_iAtlasWidth, int a_iAtlasHeight);
		void Print(const char * a_cpText, int x, int y, int a_iSize);
		void Cleanup();

	protected:

		//Standard Data
		std::vector<glm::vec2> m_Vertices;
		std::vector<glm::vec2> m_UVs;

		GLuint m_VAO;
		GLuint m_VertexBuffer;
		GLuint m_UVBuffer;
		GLuint m_ShaderProgram;

		unsigned int m_uiTexture; //Texture loaded through Soil

		//GLSL Uniforms
		GLuint m_ScreenDimensionsID; //For screen resizing
		GLuint m_TextureID; //Uniform in fragment shader

};


#endif