#version 330

// ... _screen = as screen coordinates (0 - 1024, 0-768 etc)
// ... _ndc = normalized device coordinates (-1, 1)

layout(location = 0) in vec2 position_screen;
layout(location = 1) in vec2 UV;

uniform vec2 ScreenDimensions; //To allow transition between different window sizes & resolutions

out vec2 v_UV;

void main()
{
	vec2 position_ndc = position_screen - vec2( ScreenDimensions.x / 2 , ScreenDimensions.y / 2);
	position_ndc /= vec2( ScreenDimensions.x / 2, ScreenDimensions.y / 2 );
	gl_Position = vec4(position_ndc, 0, 1);
	v_UV = UV;
}