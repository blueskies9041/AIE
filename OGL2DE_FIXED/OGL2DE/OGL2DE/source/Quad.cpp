#include "Quad.h"
#include "Misc.h"
#include "SOIL.h"
#include <iostream>

using Justin::Vertex;

Quad::Quad(const char * a_TexFilepath, int a_iWidth, int a_iHeight, int a_iFrameWidth, int a_iFrameHeight)
:	m_iWidth(a_iWidth), 
	m_iHeight(a_iHeight),
	m_v2FrameDimensions(glm::vec2((float)a_iFrameWidth, (float)a_iFrameHeight))
{

	/* Shader Program */

	m_ShaderProgram = LoadBasicShaders("resources/shaders/basic.vert", "resources/shaders/basic.frag");

	/* Texture */
	m_Texture = new Texture(a_TexFilepath);
	m_TextureID = m_ShaderProgram->GetUniform("DiffuseTexture");

	/* Vector & Matrices Initialziation  */
	m_v2FrameDimensions = glm::vec2( (float)a_iFrameWidth, (float)a_iFrameHeight);
	m_v2FrameDimensionsNorm = glm::vec2( 1.0f / ( m_Texture->GetWidth() / m_v2FrameDimensions.x ) , 1.0f / ( m_Texture->GetHeight() / m_v2FrameDimensions.y));
	m_v2UVOffset = glm::vec2(.083f * 7 , 0.0f); // Should be the idle sprite in the teleport animation row
	m_Model = glm::mat4(1.0f);

	/* VAO */
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	/* VBO */
	glGenBuffers(1, &m_VBO);

	//Vertex Structure Syntax: XYZ (Pos) RGBA (Color) UV(Texture Coordinates)

	m_aoVertices[0].Pos = glm::vec3(-0.5f,  -0.5f,  0.0f);
	m_aoVertices[1].Pos = glm::vec3(-0.5f,  0.5f,  0.0f);
	m_aoVertices[2].Pos = glm::vec3(0.5f,  -0.5f,  0.0f);
	m_aoVertices[3].Pos = glm::vec3(0.5f,  0.5f,  0.0f);

	m_aoVertices[0].Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	m_aoVertices[1].Color = glm::vec4(0.0f, 1.0f, 0.01, 1.0f);
	m_aoVertices[2].Color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	m_aoVertices[3].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	m_aoVertices[0].UV = glm::vec2 (0.0f  , 0.0);
	m_aoVertices[1].UV = glm::vec2 (0.0f  , m_v2FrameDimensionsNorm.y ); // FrameDimensionsNorm is the size of each frame in UV coordinates (75 x 75 -> really small decimals between 0 and 1)
	m_aoVertices[2].UV = glm::vec2 (m_v2FrameDimensionsNorm.x , 0.0f);
	m_aoVertices[3].UV = glm::vec2 (m_v2FrameDimensionsNorm.x , m_v2FrameDimensionsNorm.y);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), m_aoVertices , GL_STATIC_DRAW);

	/* EBO  */
	glGenBuffers(1, &m_EBO);
    GLuint elements[] = {
        0, 1, 2, 3
    };

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	/* Position Attribute*/
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(	0, // name of GL variable
							3, //size of GL variable (3 for vec3)
							GL_FLOAT, //type of variable
							GL_FALSE, //normalized?
							sizeof(Vertex), //CRITICAL: number of bytes between each position attribute xyz rgba uv = 9
							0); //how far from the start of the array the attribute occurs

	/* Color Attribute */
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(	1,
							4, 
							GL_FLOAT,
							GL_FALSE,
							sizeof(Vertex), 
							(void*)(3 * sizeof(float))); 

	/* Texture Attribute */
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(	2, 
							2, 
							GL_FLOAT,
							GL_FALSE, 
							sizeof(Vertex), 
							(void*)(7 * sizeof(float))); //each tex coord is 6 away from start of array

	glBindVertexArray(0);

	m_ShaderProgram->Use();

	/* GLSL Identifier Setup */
	m_MatrixID = m_ShaderProgram->GetUniform("MVP");
	m_UVOffsetID = m_ShaderProgram->GetUniform("UVOffset");
	

}

Quad::~Quad() {

	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteVertexArrays(1, &m_VAO);

	delete m_Texture;
	delete m_ShaderProgram;
}

void Quad::SetUVOffset(float u, float v)
{
	m_v2UVOffset = glm::vec2(u, v);
}

void Quad::SetUVOffset(glm::vec2 uv)
{
	m_v2UVOffset = uv;
}


void Quad::Draw()
{
	glBlendFunc (m_uiSourceBlendMode, m_uiDestinationBlendMode);

	m_ShaderProgram->Use();

	glActiveTexture(GL_TEXTURE0); //Choose texture unit
	glBindTexture(GL_TEXTURE_2D, m_Texture->GetObject()); //Bind texture object

	glUniform1i(m_TextureID, 0); //Communicate with fragment shader to use texture unit 0
	glUniform2f( m_UVOffsetID, m_v2UVOffset.x, m_v2UVOffset.y ); //Upload UV Offset to Shader

	//Bind Vertex Array
	glBindBuffer(m_VBO);
	glBindBuffer(m_EBO);
	glBindVertexArray(m_VAO);

	glm::mat4 MVP = g_Projection * m_Model; // Multiply Projection Matrix * Model Matrix to get MVP Matrix 

	//Upload MVP to Shader
	glUniformMatrix4fv( m_MatrixID,
						1,
						GL_FALSE,
						glm::value_ptr(MVP)); //have to use glm::value_ptr with glm




	glDrawElements(GL_TRIANGLE_STRIP, 4 , GL_UNSIGNED_INT, 0); 
	glBindVertexArray(0);
}

