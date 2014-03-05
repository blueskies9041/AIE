#version 330

in vec2 v_UV;

out vec4 f_Color;

uniform sampler2D TextureSampler;

void main()
{
	f_Color = texture2D ( TextureSampler, v_UV);
}