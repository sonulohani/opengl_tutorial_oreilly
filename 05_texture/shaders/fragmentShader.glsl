#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D myTexture1;
uniform sampler2D myTexture2;

void main()
{
   FragColor = mix(texture(myTexture1, TexCoord), texture(myTexture2, TexCoord), 0.5);
}

