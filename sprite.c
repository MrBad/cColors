#include <stdio.h>
#include <GL/glew.h>
#include <stdlib.h>
#include <stddef.h>
#include "error.h"
#include "vertex.h"
#include "sprite.h"

Sprite *spriteNew(float x, float y, float width, float height) 
{
	Sprite *sprite = calloc(1, sizeof(Sprite));
	if(!sprite) {
		fatalError("Cannot calloc a new sprite\n");
	}

	sprite->x = x;
	sprite->y = y;
	sprite->width = width;
	sprite->height = height;
	sprite->vboID = 0;

	glGenBuffers(1, &sprite->vboID);

	// construct a vertex //
	Vertex ventrices[6];
	vertexSetPos(ventrices+0, x + width, y + height);
	vertexSetPos(ventrices+1, x, y + height);
	vertexSetPos(ventrices+2, x, y);
	vertexSetPos(ventrices+3, x, y);
	vertexSetPos(ventrices+4, x + width, y);
	vertexSetPos(ventrices+5, x + width, y + height);

	for(int i = 0; i < 6; i++) {
		vertexSetColor(ventrices + i, 255, 0, 255, 255);
	}
	vertexSetColor(ventrices+1, 0, 0, 255, 255);
	vertexSetColor(ventrices+4, 0, 255, 0, 255);

	
	glBindBuffer(GL_ARRAY_BUFFER, sprite->vboID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(ventrices), ventrices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return sprite;
}

void spriteDraw(Sprite *sprite) 
{
	glBindBuffer(GL_ARRAY_BUFFER, sprite->vboID);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
			0,2,GL_FLOAT,GL_FALSE,
			sizeof(Vertex), (void*)offsetof(Vertex, pos));

	glVertexAttribPointer(
			1, 4, GL_UNSIGNED_BYTE,GL_TRUE,
			sizeof(Vertex), (void*)offsetof(Vertex, color));
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void spriteDelete(Sprite *sprite) 
{
	if(sprite) {
		if(sprite->vboID) {
			glDeleteBuffers(1, &sprite->vboID);
		}
		free(sprite);
		sprite = NULL;
	} else {
		fatalError("Trying to destroy an empty sprite");
	}
}
