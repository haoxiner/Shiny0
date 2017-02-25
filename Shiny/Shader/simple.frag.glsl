#version 400 core

uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform vec3 lightPosition;
uniform vec3 lightColor;

struct VertexOut {
    vec3 position;
    vec3 normal;
    vec2 texCoord;
};
in VertexOut vertexOut;

out vec4 fragColor;

void main() {
    vec3 l = normalize(lightPosition - vertexOut.position);
    vec3 v = normalize(-vertexOut.position);
    vec3 n = normalize(vertexOut.normal);
    vec3 h = normalize(l + v);
    float DotNH = max(0, dot(n, h));
    float DotNL = max(0, dot(n, l));
    fragColor = (0.4 + DotNL * 0.3 + pow(DotNH, 100.0) * 0.3) * vec4(lightColor, 1.0) * texture(albedoMap, vertexOut.texCoord) * texture(normalMap, vertexOut.texCoord);
}
