#version 330 core

out vec4 out_color;

in block {
       vec2 texcoord0;
} In;

uniform sampler2D texture0;

uniform int textureInversionValue;

uniform bool useSolidColor;
uniform vec3 solidColor;

void main()
{
    if(useSolidColor)
    {
        out_color = vec4(solidColor, 1.0);
    }
    else
    {
        out_color = texture(texture0, vec2(In.texcoord0.x, In.texcoord0.y * textureInversionValue));
    }
}

