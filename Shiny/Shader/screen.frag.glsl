#version 330 core

uniform sampler2D colorMap;

struct VertexOut {
    vec2 texCoord;
};
in VertexOut vertexOut;

out vec4 fragColor;

float LinearizeDepth(float z)
{
    float zNear = 0.5f;    // TODO: Replace by the zNear of your perspective projection
    float zFar  = 2000.0f; // TODO: Replace by the zFar  of your perspective projection
    float depth = z;
    return (2.0 * zNear) / (zFar + zNear - depth * (zFar - zNear));
}

void main() {
	float c = LinearizeDepth(texture(colorMap, vertexOut.texCoord).r);
	fragColor = vec4(c);
	//fragColor = vec4(vertexOut.texCoord, 0.0,1.0);
}