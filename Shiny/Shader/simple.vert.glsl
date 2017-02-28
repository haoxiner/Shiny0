#version 330 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

in vec3 position;
in vec3 normal;
in vec2 texCoord;

struct VertexOut {
    vec3 position;
    vec3 normal;
    vec2 texCoord;
};
out VertexOut vertexOut;

void main() {
    vertexOut.position = (viewMatrix * modelMatrix * vec4(position, 1.0)).xyz;
    vertexOut.normal = normalize(viewMatrix * modelMatrix * vec4(normal,0.0)).xyz;
    vertexOut.texCoord = texCoord;
    gl_Position = projectionMatrix * vec4(vertexOut.position, 1.0);
}
