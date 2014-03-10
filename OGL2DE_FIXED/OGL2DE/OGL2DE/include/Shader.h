#ifndef _SHADER_H_
#define _SHADER_H_

#include "Misc.h"
#include <string>

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
GLuint LoadShaders(const char * vertex_file_path, const char * geometry_file_path,const char * fragment_file_path);

class Shader
{

private:

	GLuint m_Object;
	unsigned * m_pRefCount;

	

public:

	Shader(const std::string& a_sShaderCode, GLenum a_ShaderType );
	Shader(const Shader& a_Other);
	~Shader();

	inline GLuint GetObject() { return m_Object; }
	void Retain();
	void Release();
	static Shader ShaderFromFile(const std::string& a_sShaderCode, GLenum a_ShaderType);
	Shader& operator=(const Shader& a_oCopy);

};

#endif