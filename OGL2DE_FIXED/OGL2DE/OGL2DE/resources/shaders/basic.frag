#version 330

// Basic fragment shader for managing color and texture of OpenGL 3.3 + Primitives

// My GLSL Syntax
	//f_Variable - variable being output by fragment shader
	// same as vertex shader syntax otherwise

in vec4 v_Color;
in vec2 v_UV;

out vec4 f_Color;
uniform sampler2D DiffuseTexture;

void main ()
{
	f_Color =  texture2D(DiffuseTexture, v_UV);
}