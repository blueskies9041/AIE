#include "Text.h"
#include "Shader.h"
#include "SOIL.h"
#include <iostream>

using Sam::LoadTexture;
using Sam::g_iWindowWidth;
using Sam::g_iWindowHeight;


/*	Text Class Overview 
		
		* My Text class was build using the 2D text tutorial at http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-11-2d-text/
			- I organized the code into a class
			- My UVs and Vertex Positions are different from his for some reason, far as I know I am doing it correctly...

		* Improvements to make eventually:
			1) Paralell this to sprite class (use model and projection matrices + UV Offsets)
			2) I don't like the re-doing vertex attribute data every frame, however since I don't understand ALL the source code I had to keep it that way, this will be fixed once I'm using all of my own code.
*/

Text::Text(const char * a_pTextureFilepath)
{
	/* Generate Vertex Buffers*/
	glGenBuffers(1, &m_VertexBuffer);
	glGenBuffers(1, &m_UVBuffer);

	/* Generate VAO */
	glGenVertexArrays(1, &m_VAO);

	/* Load in Shaders */
	m_ShaderProgram = LoadShaders("resources/shaders/text.vert", "resources/shaders/text.frag");

	/* Uniforms for Fragment Shader */
	m_ScreenDimensionsID = glGetUniformLocation( m_ShaderProgram, "ScreenDimensions");

	/* SOIL Texture Load */
	LoadTexture(a_pTextureFilepath);

	glUseProgram(m_ShaderProgram); // Run Shader program once initially.
}

Text::~Text()
{
	/* Cleanup OpenGL Objects */
	
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_UVBuffer);
	glDeleteTextures(1, &m_uiTexture);
	glDeleteProgram(m_ShaderProgram);
}

void Text::Print(const char * a_cpText, int a_iXPos, int a_iYPos, int a_iSize)
{
	unsigned int uiLength = strlen(a_cpText); //length of string to be drawn

	//Each run through of this loop will push a set of 4 Vertex Positions & UV Positions into their respective Vector containers	
	for(unsigned int i = 0 ; i < uiLength; i++)
	{
		//Vertices
		glm::vec2 v2TopLeft	 = glm::vec2( a_iXPos + i * a_iSize				, g_iWindowHeight - a_iYPos + a_iSize); //Bandaid fix so I can operate in my World Space (0 - 800, 0 - 600), fixed through note (1) above
		glm::vec2 v2TopRight = glm::vec2( a_iXPos + i * a_iSize + a_iSize	, g_iWindowHeight - a_iYPos + a_iSize);
		glm::vec2 v2BotRight = glm::vec2( a_iXPos + i * a_iSize + a_iSize	, g_iWindowHeight - a_iYPos );
		glm::vec2 v2BotLeft	 = glm::vec2( a_iXPos + i * a_iSize				, g_iWindowHeight - a_iYPos );

		m_Vertices.push_back(v2TopLeft);
		m_Vertices.push_back(v2BotLeft);
		m_Vertices.push_back(v2TopRight);
		m_Vertices.push_back(v2BotRight);

		//Really ghetto way of navigating sprite sheet to the appropriate character
		//Text Sprite Sheet has 16 x 16 Character Sprites
		char cCharacter = a_cpText[i];
		float fUV_x = (cCharacter % 16) / 16.0f; // Example, if cCharacter is capital 'A' (ASCII value of 65) then (65 % 16 = 1).
		float fUV_y = (cCharacter / 16) / 16.0f; //																   (65 / 16 = 4).
												 //Therefore : Col 1, Row 4 is Captital A. Both numbers are then divided by 16 to fit into the 0 - 1 UV Range.


		//UVs
		glm::vec2 v2BotLeftUV	= glm::vec2( fUV_x					,  fUV_y ); // So for letter 'A', (65 % 16) / 16 = .0625 . (65/16) / 16 = .25. Top left UV Coordinate of 'A' is (.0625 , .25)
		glm::vec2 v2TopLeftUV	= glm::vec2( fUV_x					,  fUV_y + 1.0f / 16.0f );
		glm::vec2 v2BotRightUV	= glm::vec2( fUV_x + 1.0f / 16.0f	,  fUV_y );
		glm::vec2 v2TopRightUV	= glm::vec2( fUV_x + 1.0f / 16.0f	,  fUV_y + 1.0f / 16.0f);

		m_UVs.push_back(v2BotLeftUV);
		m_UVs.push_back(v2TopLeftUV);
		m_UVs.push_back(v2BotRightUV);
		m_UVs.push_back(v2TopRightUV);
	}

	/* Bind Buffers (Both Vertex Buffers & VAO) */
	glBindVertexArray(m_VAO);
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

	//Bind Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_uiTexture);
	glUniform1i( m_TextureID, 0); //Texture Uniform in Shader
	glUniform2f(m_ScreenDimensionsID, (float)g_iWindowWidth, (float)g_iWindowHeight); //passes global screen dimensions to vShader "text.vert"

	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_Vertices.size());
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindVertexArray(0);

}

void Text::LoadTexture(const char* a_TexFilepath)
{
	/* OpenGL Texture Object */
	m_uiTexture = 0;
	glGenTextures(1, &m_uiTexture);
	glActiveTexture (GL_TEXTURE0);
	glBindTexture( GL_TEXTURE_2D, m_uiTexture);

	/* SOIL Image Load */
	unsigned char* image = SOIL_load_image(a_TexFilepath, &m_iTextureWidth, &m_iTextureHeight, 0, SOIL_LOAD_RGBA); //Create data using SOIL to pass to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_iTextureWidth, m_iTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image); //Pass data to OpenGL (Go learn more about this later)
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	m_TextureID = glGetUniformLocation (m_ShaderProgram, "TextureSampler"); //Align TextureID with uniform in fragment shader
}


