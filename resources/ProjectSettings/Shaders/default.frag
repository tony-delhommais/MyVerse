#version 330 core
out vec4 FragColor;
  
in vec3 Normal;
in vec2 TexCoord;

uniform int textureInversion = -1;
uniform sampler2D diffuseTexture;

uniform vec3 solidColor = vec3(0, 0, 0);

void main()
{
    FragColor = texture(diffuseTexture, vec2(TexCoord.x, TexCoord.y * textureInversion)) + vec4(solidColor, 1.0);
}

