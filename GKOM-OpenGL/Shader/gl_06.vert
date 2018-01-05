#version 300 es

layout (location = 0) in lowp vec3 position;
layout (location = 1) in lowp vec3 color;
layout (location = 2) in lowp vec2 texCoord;
layout (location = 3) in lowp vec3 normal;


out lowp vec2 vTexCoord;
out lowp vec3 vNormal;
out lowp vec3 vPosition;
out lowp vec3 vColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vTexCoord = texCoord;
    vPosition = (model * vec4(position, 1.0)).xyz;
    vNormal = mat3(transpose(inverse(model))) * normal;
    vColor = color;
    gl_Position = projection * view * model * vec4(position, 1.0f);
}
