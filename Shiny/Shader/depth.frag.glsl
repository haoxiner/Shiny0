#version 430 core

//out vec4 fragColor;

//float LinearizeDepth()
//{
//    float zNear = 0.5f;    // TODO: Replace by the zNear of your perspective projection
//    float zFar  = 2000.0f; // TODO: Replace by the zFar  of your perspective projection
//    float depth = gl_FragCoord.z;
//    return (2.0 * zNear) / (zFar + zNear - depth * (zFar - zNear));
//}

void main() {
	//fragColor = vec4(gl_FragCoord.z / gl_FragCoord.w);
	//float Z = projectionMatrix[3].z/(gl_FragDepth * -2.0 + 1.0 - projectionMatrix[2].z);
	//float c = LinearizeDepth();
	//fragColor = vec4(c);
	//fragColor.w = 1.0;
}