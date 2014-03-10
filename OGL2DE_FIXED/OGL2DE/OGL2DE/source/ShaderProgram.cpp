#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::vector<Shader> a_Shaders) : m_Object(0)
{
	if(a_Shaders.size() <= 0)
		throw std::runtime_error("No shaders were provided to create the program");

	//create the program object
	m_Object = glCreateProgram();
	if(m_Object == 0)
		throw std::runtime_error("glCreateProgram failed");

	//attach all the shaders
    for(unsigned i = 0; i < a_Shaders.size(); ++i)
        glAttachShader(m_Object, a_Shaders[i].GetObject());

	//link the shaders together
    glLinkProgram(m_Object);

	//detach all the shaders
    for(unsigned i = 0; i < a_Shaders.size(); ++i)
        glDetachShader(m_Object, a_Shaders[i].GetObject());

	//throw exception if linking failed
    GLint status;
    glGetProgramiv(m_Object, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        std::string msg("Program linking failure: ");
        
        GLint infoLogLength;
        glGetProgramiv(m_Object, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetProgramInfoLog(m_Object, infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;
        
        glDeleteProgram(m_Object); m_Object = 0;
        throw std::runtime_error(msg);
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
		throw std::runtime_error("Attribute Name argument was NULL");

	GLint attrib = glGetAttribLocation(m_Object, a_pAttributeName);
	if(attrib == -1)
		throw std::runtime_error(std::string("Program Attribute not found: ") + a_pAttributeName);

	return attrib;
}

GLint ShaderProgram::GetUniform(const GLchar * a_pUniformName) const
{
	if(!a_pUniformName)
		throw std::runtime_error("Uniform Name argument was NULL");

	GLint uniform = glGetUniformLocation(m_Object, a_pUniformName);
	if(uniform == -1)
		throw std::runtime_error(std::string("Program Uniform not found: ") + a_pUniformName);

	return uniform;
}

// returns a new tdogl::Program created from the given vertex and fragment shader filenames
ShaderProgram * LoadBasicShaders(const char* vertFilename, const char* fragFilename) {
    std::vector<Shader> shaders;
    shaders.push_back(Shader::ShaderFromFile(vertFilename, GL_VERTEX_SHADER));
    shaders.push_back(Shader::ShaderFromFile(fragFilename, GL_FRAGMENT_SHADER));
    return new ShaderProgram(shaders);
}

