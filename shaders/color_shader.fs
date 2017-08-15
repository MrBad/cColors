#version 130

// ->
in vec2 fragmentPosition;
in vec4 fragmentColor;

out vec4 color;

uniform float time;

void main()
{
//	color = vec4(0.4, 0.0, 0.0, 1.0);
	color = vec4(fragmentColor.r * (cos(fragmentPosition.x*4 + time)+ 1.0) * 0.5,
				 fragmentColor.g * (cos(fragmentPosition.y*6 + time)+ 1.0) * 0.5,
				 fragmentColor.b * (cos(fragmentPosition.x*2 * 0.4 + time)+ 1.0) * 0.3,
	fragmentColor.a);


/*	color = fragmentColor + vec4(
			1.0 * (cos(time) + 1.0) * 0.5,
			1.0 * (cos(time) + 2.0) * 0.5,
			1.0 * (sin(time) + 1.0) * 0.5,
			0.0);

*/
}
