#version 150

// Fragment Shader
// All Pixels in a Polygon
in vec2 fragmentPosition;
in vec4 fragmentColor;

out vec4 color;

uniform float time;

void main () {
	/*color =  fragmentColor + vec4 (
			1.0 * (cos (time) + 1.0) * 0.5,
			1.0 * (cos (time + 2.0) + 1.0) * 0.5,
			1.0 * (sin (time + 1.0) + 1.0) * 0.5,
			0.0);*/
	color = vec4 (
			fragmentColor.r * (cos (fragmentPosition.x + time) + 1.0) * 0.5,
			fragmentColor.g * (cos (fragmentPosition.x + time) + 1.0) * 0.5,
			fragmentColor.b * (cos (fragmentPosition.x + time) + 1.0) * 0.5,
			fragmentColor.a);

}
