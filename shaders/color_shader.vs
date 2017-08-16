// vertex shader
#version 130

// specify inputs

in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec4 fragmentColor;
out vec2 fragmentPosition;
out vec2 fragmentUV;

void main()
{
	gl_Position.xy = vertexPosition; // sets position
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;

	fragmentColor = vertexColor;
	fragmentPosition = vertexPosition;
	fragmentUV = vertexUV;
}
