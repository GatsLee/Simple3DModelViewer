#version 330

in vec2 TexCoord;
in vec3 Normal;

out vec4 colour;

uniform sampler2D diffuseTexture;
//uniform int activeTextureIndex;
uniform bool useDefaultColour;

//uniform vec3 lightPos;
//uniform vec3 viewPos;
//uniform vec3 ambientColour;
//uniform vec3 eyePosition;

void main()
{
    vec3 defaultColour = vec3(1.0, 1.0, 1.0);
    vec3 textureColour = texture(diffuseTexture, TexCoord).rgb;

    if (useDefaultColour)
    {
        colour = vec4(defaultColour, 1.0);
    }
    else
    {
        colour = vec4(textureColour, 1.0);
    }
}