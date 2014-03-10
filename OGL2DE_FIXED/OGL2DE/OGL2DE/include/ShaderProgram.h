#ifndef _SHADERPROGRAM_H_
#define _SHADERPROGRAM_H_

#include "Shader.h"
#include <vector>

class ShaderProgram
{
public:

	ShaderProgram(const std::vector<Shader> a_Shaders);
	~ShaderProgram();

	void Use();
	bool InUse();
	void StopUsing();

	GLint GetAttribute(const GLchar* a_pAttributeName) const;
	GLint GetUniform(const GLchar* a_pUniformName) const;

	inline GLuint GetObject() { return m_Object; }

private:

	GLuint m_Object;
	
};

// returns a new tdogl::Program created from the given vertex and fragment shader filenames
ShaderProgram * LoadBasicShaders(const char* vertFilename, const char* fragFilename);


#endif