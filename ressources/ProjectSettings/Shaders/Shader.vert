#version 330 core

in vec3 in_position;
in vec3 in_normal;
in vec2 in_texcoord0;

uniform mat4 modelViewProjectionMatrix;

out block {
       vec2 texcoord0;
} Out;

void main()
{
    gl_Position = modelViewProjectionMatrix * vec4(in_position, 1.0);
	
	Out.texcoord0 = in_texcoord0;
}
