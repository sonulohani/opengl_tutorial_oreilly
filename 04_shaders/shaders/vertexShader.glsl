#version 330 core
layout (location = 0) in vec3 aPos;
uniform vec2 posOffset;

void main()
{
   gl_Position = vec4(aPos.x + posOffset.x, aPos.y + posOffset.y, aPos.z, 1.0);
}

