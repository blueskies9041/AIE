#include "Quad.h"
#include "Misc.h"
#include "Shader.h"
#include "Texture.h"
#include "SOIL.h"
#include "GLLOG.h"
#include "TextFileReader.h"

using Justin::Vertex;

Quad::Quad(const char * a_TexFilepath, int a_iWidth, int a_iHeight, int a_iTexWidth, int a_iTexHeight, int a_iFrameWidth, int a_iFrameHeight)
	: m_iQuadWidth(a_iWidth), m_iQuadHeight(a_iHeight),
	  m_iTextureWidth(a_iTexWidth), m_iTextureHeight(a_iTexHeight),
	  m_v2FrameDimensions(glm::vec2((float)a_iFrameWidth, (float)a_iFrameHeight))
{

	/* Shader Program */
	
	LoadVertShader("resources/shaders/basic.vert");
	LoadFragShader("resources/shaders/basic.frag");
	LinkShaders();
	
	/* Generate Buffers */

	glGenBuffers(1, &m_glVBO);
	glGenBuffers(1, &m_glEBO);
	glGenVertexArrays(1, &m_glVAO);

	/* Bind Buffers */

	glBindVertexArray(m_glVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_glVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_glEBO);

		/* Vertex Data: Positions */
		m_aoVertices[0].Pos = glm::vec3(-0.5f,  -0.5f,  0.0f);
		m_aoVertices[1].Pos = glm::vec3(-0.5f,  0.5f,  0.0f);
		m_aoVertices[2].Pos = glm::vec3(0.5f,  -0.5f,  0.0f);
		m_aoVertices[3].Pos = glm::vec3(0.5f,  0.5f,  0.0f);

		/* Vertex Data: Color */
		m_aoVertices[0].Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		m_aoVertices[1].Color = glm::vec4(0.0f, 1.0f, 0.01, 1.0f);
		m_aoVertices[2].Color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		m_aoVertices[3].Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		/* Vertex Data: UV Coordinates */
		m_aoVertices[0].UV = glm::vec2 (0.0f  , 0.0);
		m_aoVertices[1].UV = glm::vec2 (0.0f  , m_v2FrameDimensionsNorm.y );
		m_aoVertices[2].UV = glm::vec2 (m_v2FrameDimensionsNorm.x , 0.0f);
		m_aoVertices[3].UV = glm::vec2 (m_v2FrameDimensionsNorm.x , m_v2FrameDimensionsNorm.y);

		/* Elements Array  */

		GLuint elements[] = {
			0, 1, 2, 3
		};

	/* Buffering */

	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), m_aoVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	/* Specify Data Layout */

	GLint posAttrib = glGetAttribLocation(m_ShaderProgram,"position");
	glEnableVertexAttribArray(posAttrib);
	GLint colAttrib = glGetAttribLocation(m_ShaderProgram,"color");
	glEnableVertexAttribArray(colAttrib);
	GLint uvAttrib = glGetAttribLocation(m_ShaderProgram,"texcoord");
	glEnableVertexAttribArray(uvAttrib);

		/* Position Attribute*/
		glVertexAttribPointer(	posAttrib, // name of GL variable
								3, //size of GL variable (3 for vec3)
								GL_FLOAT, //type of variable
								GL_FALSE, //normalized?
								sizeof(Vertex), //CRITICAL: number of bytes between each position attribute xyz rgba uv = 9
								0); //how far from the start of the array the attribute occurs

		/* Color Attribute */
		glVertexAttribPointer(	colAttrib,
								4, 
								GL_FLOAT,
								GL_FALSE,
								sizeof(Vertex), 
								(void*)(3 * sizeof(float))); 

		/* Texture Attribute */
		glVertexAttribPointer(	uvAttrib, 
								2, 
								GL_FLOAT,
								GL_FALSE, 
								sizeof(Vertex), 
								(void*)(7 * sizeof(float))); //each tex coord is 6 away from start of array

	glBindVertexArray(0);

	/* Vector & Matrices Initialziation  */
	m_v2FrameDimensions = glm::vec2( (float)a_iFrameWidth, (float)a_iFrameHeight);
	m_v2FrameDimensionsNorm = glm::vec2( 1.0f / ( m_iTextureWidth / m_v2FrameDimensions.x ) , 1.0f / ( m_iTextureHeight / m_v2FrameDimensions.y));
	m_v2UVOffset = glm::vec2(.083f * 7 , 0.0f); // Should be the idle sprite in the teleport animation row
	m_Model = glm::mat4(1.0f);
	
	/* GLSL Identifier Setup */
	m_glMatrixID = glGetUniformLocation(m_ShaderProgram, "MVP");
	m_glTextureID = glGetUniformLocation(m_ShaderProgram, "DiffuseTexture");
	m_glUVOffsetID = glGetUniformLocation(m_ShaderProgram, "UVOffset");

}

Quad::~Quad() {
}

void Quad::SetUVOffset(float u, float v)
{
	m_v2UVOffset = glm::vec2(u, v);
}

void Quad::SetUVOffset(glm::vec2 uv)
{
	m_v2UVOffset = uv;
}

void Quad::LoadTexture(const char * a_TexFilepath)
{
	/* Texture Loading through SOIL */

	m_uiTexture = 0;

	m_SourceBlendMode = GL_SRC_ALPHA;
	m_DestinationBlendMode = GL_ONE_MINUS_SRC_ALPHA;

	glGenTextures(1, &m_uiTexture);
	glActiveTexture(GL_TEXTURE0);
	
	int iWidth, iHeight;
	unsigned char* cpImage = SOIL_load_image(a_TexFilepath, &iWidth, &iHeight, 0, SOIL_LOAD_RGBA);

	glBindTexture( GL_TEXTURE_2D, m_uiTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, cpImage);
	SOIL_free_image_data(cpImage);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}


void Quad::Draw()
{
	glBlendFunc( m_SourceBlendMode, m_DestinationBlendMode);
	glUseProgram(m_ShaderProgram);

	/* Texture Business */
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_uiTexture);
	glUniform1i( m_glTextureID, 0);

	glUniform2f( m_glUVOffsetID, m_v2UVOffset.x, m_v2UVOffset.y );

	glBindBuffer(GL_ARRAY_BUFFER, m_glVBO);
	glBindVertexArray(m_glVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_glEBO);

	glBufferData(GL_ARRAY_BUFFER, 4* sizeof(Vertex), m_aoVertices, GL_STATIC_DRAW);

	/* Draw Call */
	glDrawElements(GL_TRIANGLE_STRIP, 4 , GL_UNSIGNED_INT, (void*) 0); 


}

bool Quad::LoadVertShader(const char* filePath)
{
	std::string vs =textFileReader(filePath);
	const char * VertexShader = vs.c_str();
	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VertexShader, 1, &VertexShader, NULL);
	glCompileShader(m_VertexShader);
	
	return printShaderInfoLog(m_VertexShader);
}
bool Quad::LoadFragShader(const char* filePath)
{
	std::string vs =textFileReader(filePath);
	const char * FragmentShader = vs.c_str();
	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShader, 1, &FragmentShader, NULL);
	glCompileShader(m_FragmentShader);
	
	return printShaderInfoLog(m_FragmentShader);

}
bool Quad::LinkShaders()
{
	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_VertexShader);

	glLinkProgram(m_ShaderProgram);
	glUseProgram(m_ShaderProgram);
	
	return printProgramInfoLog(m_ShaderProgram);
}

void Quad::Cleanup()
{
	glDeleteTextures(1, &m_uiTexture);
	glDeleteShader(m_ShaderProgram);
	glDeleteBuffers(1, &m_glVBO);
	glDeleteBuffers(1, &m_glEBO);
	glDeleteVertexArrays(1, &m_glVAO);
}