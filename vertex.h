#ifndef VERTEX_H
#define VERTEX_H

#include <GL/glew.h>

typedef struct {
	float x, y;
} Position;

typedef struct {
	GLubyte r,g,b,a;
} Color;

typedef struct {
	Position pos;
	Color color;
} Vertex;

int vertexSetPos(Vertex *v, float x, float y);
int vertexSetColor(Vertex *v, float r, float g, float b, float a);

#endif
