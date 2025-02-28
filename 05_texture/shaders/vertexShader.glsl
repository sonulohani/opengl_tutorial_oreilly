#version 330 core
layout (location = 0) in vec3 aPos;
layout (location=1) in vec2 textCoord;

out vec2 TexCoord;

uniform vec2 posOffset;

void main()
{
   gl_Position = vec4(aPos.x + posOffset.x, aPos.y + posOffset.y, aPos.z, 1.0);
   TexCoord = textCoord;
}

