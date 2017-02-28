#version 330 core

in vec2 position;
in vec2 texCoord;

struct VertexOut {
    vec2 texCoord;
};
out VertexOut vertexOut;

void main() {
	vertexOut.texCoord = texCoord;
	gl_Position = vec4(position, 0.0, 1.0);
}