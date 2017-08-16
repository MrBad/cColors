#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "window.h"
#include "error.h"
#include "sprite.h"
#include "gl_program.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

enum {
	GAME_PLAYING,
	GAME_OVER,
};

int main()
{
	Window *window;
	int status = GAME_PLAYING;
	Sprite* sprite = NULL;
	GLProgram* program = NULL;

	window = windowNew("Colors in C", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	
	sprite = spriteNew(-1.0f, -1.0f, 2.0f, 2.0f);
	
	program = glProgramNew();
	glProgramCompileShaders(program, "shaders/color_shader");
	glProgramAddAttribute(program, "vertexPosition");
	glProgramAddAttribute(program, "vertexColor");
	glProgramLinkShaders(program);


	float time = 0;
	while(status == GAME_PLAYING) {
		if(windowHandleEvents(window)) {
			status = GAME_OVER;
		}

		time += 0.05f;
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glProgramUse(program);
	
		GLint timeLocation = glGetUniformLocation(program->programID, "time");
		glUniform1f(timeLocation, time);

		spriteDraw(sprite);

		glProgramUnuse(program);
		
		windowUpdate(window);
	}

	glProgramDelete(program);
	spriteDelete(sprite);
	
	windowDestroy(window);
}
