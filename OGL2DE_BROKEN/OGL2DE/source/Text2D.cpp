#include "Text2D.h"
#include "Shader.h"
#include "SOIL.h"

using Sam::LoadTexture;
using Sam::g_iWindowWidth;
using Sam::g_iWindowHeight;


void Text::Init(const char * a_cpTexturePath, int a_iAtlasWidth, int a_iAtlasHeight)
{
	// Gen Buffers
	glGenBuffers(1, &m_VertexBuffer);
	glGenBuffers(1, &m_UVBuffer);

	// Init Shader
	m_ShaderProgram = LoadShaders("resources/shaders/text.vert", "resources/shaders/text.frag");

	// Init Shader Uniform(s)
	m_ScreenDimensionsID = glGetUniformLocation( m_ShaderProgram, "ScreenDimensions");
	m_TextureID = glGetUniformLocation (m_ShaderProgram, "TextureSampler" );

	// SOIL Texture Load
	m_uiTexture = 0;
	glGenTextures(1, &m_uiTexture);
	glActiveTexture(GL_TEXTURE0);
	
	int iWidth, iHeight;
	unsigned char* cpImage = SOIL_load_image(a_cpTexturePath, &iWidth, &iHeight, 0, SOIL_LOAD_RGBA);
	glBindTexture( GL_TEXTURE_2D, m_uiTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, cpImage);
	SOIL_free_image_data(cpImage);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Text::Print(const char * a_cpText, int a_iXPos, int a_iYPos, int a_iSize)
{
	unsigned int uiLength = strlen(a_cpText); //length of string to be drawn

	glUniform2f(m_ScreenDimensionsID, (float)g_iWindowWidth, (float)g_iWindowHeight); //passes global screen dimensions to text vertex shader

	//Fill Vertex & UV Buffers
	for(unsigned int i = 0 ; i < uiLength; i++)
	{
		//Vertices
		glm::vec2 v2TopLeft	 = glm::vec2( a_iXPos + i * a_iSize				, a_iYPos + a_iSize);
		glm::vec2 v2TopRight = glm::vec2( a_iXPos + i * a_iSize + a_iSize	, a_iYPos + a_iSize);
		glm::vec2 v2BotRight = glm::vec2( a_iXPos + i * a_iSize + a_iSize	, a_iYPos );
		glm::vec2 v2BotLeft	 = glm::vec2( a_iXPos + i * a_iSize				, a_iYPos );

		// Gonna use GL_TRIANGLES at first and switch to triangle strip later

		m_Vertices.push_back(v2TopLeft);
		m_Vertices.push_back(v2BotLeft);
		m_Vertices.push_back(v2TopRight);
		m_Vertices.push_back(v2BotRight);

		// Figure this out
		char cCharacter = a_cpText[i];
		float fUV_x = (cCharacter%16)/16.0f;
		float fUV_y = (cCharacter/16)/16.0f;

		//UVs
		glm::vec2 v2BotLeftUV	= glm::vec2( fUV_x					,  fUV_y );
		glm::vec2 v2TopLeftUV	= glm::vec2( fUV_x					,  fUV_y + 1.0f / 16.0f );
		glm::vec2 v2BotRightUV	= glm::vec2( fUV_x + 1.0f / 16.0f	,  fUV_y );
		glm::vec2 v2TopRightUV	= glm::vec2( fUV_x + 1.0f / 16.0f	,  fUV_y + 1.0f / 16.0f);

		m_UVs.push_back(v2BotLeftUV);
		m_UVs.push_back(v2TopLeftUV);
		m_UVs.push_back(v2BotRightUV);
		m_UVs.push_back(v2TopRightUV);
	}


	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(glm::vec2), &m_Vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_UVs.size() * sizeof(glm::vec2), &m_UVs[0], GL_STATIC_DRAW);

	//Bind Shader
	glUseProgram(m_ShaderProgram);

	// Attribute #1 : Vertices 
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Attribute #2 : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Draw
	//Texture Shit

	//Bind Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_uiTexture);
	glUniform1i( m_TextureID, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_Vertices.size());

}

void Text::Cleanup() 
{
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_UVBuffer);
	glDeleteTextures(1, &m_uiTexture);
	glDeleteProgram(m_ShaderProgram);
}

