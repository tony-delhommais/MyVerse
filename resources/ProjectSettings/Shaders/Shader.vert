#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 ModelMatrix;
uniform mat4 VueProjectionMatrix;

out vec3 Normal;
out vec2 TexCoord;

void main()
{
    gl_Position = VueProjectionMatrix * ModelMatrix * vec4(aPosition, 1.0);
	
	Normal = aNormal;
	TexCoord = aTexCoord;
}
