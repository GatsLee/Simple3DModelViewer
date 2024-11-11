#version 330

in vec4 vColour;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 colour;

uniform sampler2D theTexture;

uniform vec3 eyePosition;

void main()
{
    //colour = texture(theTexture, TexCoord) * vColour;
    colour = vColour;
}