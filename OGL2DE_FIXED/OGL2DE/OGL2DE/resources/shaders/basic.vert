#version 330

// Basic vertex shader for managing translation, color, and texture of OpenGL 3.3 + Primitives

// My GLSL Syntax
	// v_Variable - Variable being output by vertex shader
	// varible - In variables that are passed into  vertex shader
	// Variable - Uniforms

layout (location = 0) in vec3 position; 
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texcoord;

uniform mat4 MVP; // Model * View * Projection Matrix
uniform vec2 UVOffset; //

out vec2 v_UV;
out vec4 v_Color;

void main() 
{
	v_UV = vec2(texcoord.x + UVOffset.x, texcoord.y + UVOffset.y); 
	gl_Position = MVP *  vec4 (position, 1.0);
	v_Color = color;
}
