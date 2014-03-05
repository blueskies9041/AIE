#ifndef _SHADER_H_
#define _SHADER_H_

#include "Misc.h"

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
GLuint LoadShaders(const char * vertex_file_path, const char * geometry_file_path,const char * fragment_file_path);

#endif