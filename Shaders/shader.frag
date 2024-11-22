#version 330

in vec4 vColour;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 colour;

uniform sampler2D theTexture;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

//uniform vec3 lightPos;
//uniform vec3 viewPos;
//uniform vec3 ambientColour;
//uniform vec3 eyePosition;

uniform bool useDiffuseTexture;
uniform bool useSpecularTexture;
uniform bool useNormalTexture;

void main()
{
    // Sample textures
   // vec3 diffuseTexture = texture(diffuseTexture, TexCoord).rgb;
    //vec3 specularTexture = texture(specularTexture, TexCoord).rgb;

    // ambient component
    //vec3 ambient = ambientColour * diffuseTexture;

    // diffuse component
    //vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(lightPos - FragPos);
    //float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = diff * diffuseTexture;

    // specular component
    //vec3 viewDir = normalize(viewPos - FragPos);
    //vec3 reflectDir = reflect(-lightDir, norm);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
   //vec3 specular = specularTexture * spec;
    
    // end result
    //vec3 result = (ambient + diffuse + specular) * vColour.rgb;
    //colour = vec4(result, 1.0);

    vec4 finalColour = vec4(0.0, 0.0, 0.0, 1.0);
    // Sample textures
    if (useDiffuseTexture)
    {
        finalColour += texture(diffuseTexture, TexCoord);
    }
    if (useSpecularTexture)
    {
        finalColour += texture(specularTexture, TexCoord);
    }
    if (useNormalTexture)
    {
        finalColour += texture(normalTexture, TexCoord);
    }

    finalColour = clamp(finalColour, 0.0, 1.0);

    colour = finalColour;
}