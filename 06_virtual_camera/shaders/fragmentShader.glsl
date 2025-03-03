#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D myTexture1;

void main()
{
   FragColor = texture(myTexture1, TexCoord);
}

