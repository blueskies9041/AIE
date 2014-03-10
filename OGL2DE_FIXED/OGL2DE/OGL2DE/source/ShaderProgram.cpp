#include "ShaderProgram.h"
#include <iostream>

ShaderProgram::ShaderProgram(std::vector<Shader> a_Shaders) : m_Object(0)
{
	if(a_Shaders.size() <= 0)
		std::cout << ("No shaders were provided to create the program") << endl;

	//create the program object
	m_Object = glCreateProgram();
	if(m_Object == 0)
		std::cout << ("glCreateProgram failed\n");

	//attach all the shaders
    for(unsigned i = 0; i < a_Shaders.size(); ++i)
        glAttachShader(m_Object, a_Shaders[i].GetObject());

	//link the shaders together
    glLinkProgram(m_Object);

	//detach all the shaders
    for(unsigned i = 0; i < a_Shaders.size(); ++i)
        glDetachShader(m_Object, a_Shaders[i].GetObject());

	GLint Result;
	int iInfoLogLength;
	//Check program
	glGetProgramiv(m_Object, GL_LINK_STATUS, &Result);
	glGetProgramiv(m_Object, GL_INFO_LOG_LENGTH, &iInfoLogLength);
	if(iInfoLogLength < 0)
	{
		std::vector<char> ShaderProgErrMsg(iInfoLogLength + 1);
		glGetShaderInfoLog(m_Object, iInfoLogLength, NULL, &ShaderProgErrMsg[0]);
		std::cout<< ("%s\n", &ShaderProgErrMsg[0]);
	}

}


ShaderProgram::~ShaderProgram()
{
	 if(m_Object != 0)
		 glDeleteProgram(m_Object);
}

void ShaderProgram::Use()
{
	glUseProgram(m_Object);
}

bool ShaderProgram::InUse()
{
	GLint currentProgram = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

	return (currentProgram == (GLint)m_Object);
}

void ShaderProgram::StopUsing()
{
	assert(InUse());
	glUseProgram(0);
}

GLint ShaderProgram::GetAttribute(const GLchar* a_pAttributeName) const
{
	if(!a_pAttributeName)
		std::cout << ("Attribute Name argument was NULL\n");

	GLint attrib = glGetAttribLocation(m_Object, a_pAttributeName);
	if(attrib == -1)
		std::cout << (std::string("Program Attribute not found: ") + a_pAttributeName +"\n");

	return attrib;
}

GLint ShaderProgram::GetUniform(const GLchar * a_pUniformName) const
{
	if(!a_pUniformName)
		std::cout << ("Uniform Name argument was NULL");

	GLint uniform = glGetUniformLocation(m_Object, a_pUniformName);
	if(uniform == -1)
		std::cout << (std::string("Program Uniform not found: ") + a_pUniformName + "\n");

	return uniform;
}

// returns a new tdogl::Program created from the given vertex and fragment shader filenames
ShaderProgram * LoadBasicShaders(const char* vertFilename, const char* fragFilename)
{
    std::vector<Shader> shaders;
    shaders.push_back(Shader::ShaderFromFile(vertFilename, GL_VERTEX_SHADER));
    shaders.push_back(Shader::ShaderFromFile(fragFilename, GL_FRAGMENT_SHADER));
    return new ShaderProgram(shaders);
}

