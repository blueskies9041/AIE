#include "Quad.h"
#include "Misc.h"
#include "Shader.h"
#include "Texture.h"

using Justin::Vertex;

CQuad::CQuad(const char * a_TexFilepath, int a_iWidth, int a_iHeight, int a_iTexWidth, int a_iTexHeight, int a_iFrameWidth, int a_iFrameHeight)
	: m_iQuadWidth(a_iWidth), m_iQuadHeight(a_iHeight),
	  m_iTextureWidth(a_iTexWidth), m_iTextureHeight(a_iTexHeight),
	  m_v2FrameDimensions(glm::vec2((float)a_iFrameWidth, (float)a_iFrameHeight))
{

	/* Vector & Matrices Initialziation  */
	m_v2FrameDimensions = glm::vec2( (float)a_iFrameWidth, (float)a_iFrameHeight);
	m_v2UVUnit = glm::vec2( 1.0f / ( m_iTextureWidth / m_v2FrameDimensions.x ) , 1.0f / ( m_iTextureHeight / m_v2FrameDimensions.y));
	m_v2UVOffset = glm::vec2(.083f * 7 , 0.0f); // Should be the idle sprite in the teleport animation row
	m_Model = glm::mat4(1.0f);

	/* Shader Program */
	m_glShaderProgram = LoadShaders("resources/shaders/basic.vert", "resources/shaders/basic.frag");

	/* VAO */
	glGenVertexArrays(1, &m_glVAO);
	glBindVertexArray(m_glVAO);

	/* VBO */
	glGenBuffers(1, &m_glVBO);

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
	m_aoVertices[1].UV = glm::vec2 (0.0f  , m_v2UVUnit.y );
	m_aoVertices[2].UV = glm::vec2 (m_v2UVUnit.x , 0.0f);
	m_aoVertices[3].UV = glm::vec2 (m_v2UVUnit.x , m_v2UVUnit.y);

	glBindBuffer(GL_ARRAY_BUFFER, m_glVBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), m_aoVertices , GL_STATIC_DRAW);

	
	/* EBO  */
	glGenBuffers(1, &m_glEBO);
    GLuint elements[] = {
        0, 1, 2, 3
    };

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_glEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	/* Texture Loading through SOIL */

	glGenTextures(1, &m_glTexture);
	glActiveTexture(GL_TEXTURE0);
	m_glTexture = LoadTexture(a_TexFilepath, a_iTexWidth, a_iTexHeight);

	/* GLSL Identifier Setup */
	m_glMatrixID = glGetUniformLocation(m_glShaderProgram, "MVP");
	m_glTextureID = glGetUniformLocation(m_glShaderProgram, "DiffuseTexture");
	m_glUVOffsetID = glGetUniformLocation(m_glShaderProgram, "UVOffset");
	

}

CQuad::~CQuad() {
}

void CQuad::SetUVOffset(float u, float v)
{
	m_v2UVOffset = glm::vec2(u, v);
}

void CQuad::Update()
{
	glUseProgram(m_glShaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glm::mat4 MVP = Projection * m_Model;
	glUniformMatrix4fv( m_glMatrixID,
						1,
						GL_FALSE,
						glm::value_ptr(MVP)); //have to use glm::value_ptr with glm

	glUniform2f( m_glUVOffsetID, m_v2UVOffset.x, m_v2UVOffset.y );

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

	glDrawElements(GL_TRIANGLE_STRIP, 4 , GL_UNSIGNED_INT, 0); 
}

