#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
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
	SDL_Window* window;
	SDL_GLContext glContext;
	SDL_Event event;
	int status = GAME_PLAYING;
	Sprite* sprite = NULL;
	GLProgram* program = NULL;

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fatalError("SDL_Init: %s", SDL_GetError());
	}

	window = SDL_CreateWindow(
			"Colors in C", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

	if(window == NULL) {
		fatalError("Cannot create window: %s\n", SDL_GetError());
	}

	glContext = SDL_GL_CreateContext(window);
	if(glContext == NULL) {
		fatalError("Cannot create opengl context: %s\n", SDL_GetError());
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if(glewInit() != GLEW_OK) {
		fatalError("Cannot init glew\n");
	}

	glClearColor(0, 0, 0.3, 1);

	sprite = spriteNew(-1.0f, -1.0f, 2.0f, 2.0f);


	program = glProgramNew();
	glProgramCompileShaders(program, "shaders/color_shader");
	glProgramAddAttribute(program, "vertexPosition");
	glProgramAddAttribute(program, "vertexColor");
	glProgramLinkShaders(program);


	float time = 0;
	while(status == GAME_PLAYING) {
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				status = GAME_OVER;
			} else if(event.type == SDL_KEYDOWN) {
				if(event.key.keysym.sym == SDLK_ESCAPE) {
					status = GAME_OVER;
				}
			}
		}

		time += 0.05f;
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glProgramUse(program);
	
		GLint timeLocation = glGetUniformLocation(program->programID, "time");
		glUniform1f(timeLocation, time);

		spriteDraw(sprite);

		glProgramUnuse(program);

		SDL_GL_SwapWindow(window);
	}

	glProgramDelete(program);
	spriteDelete(sprite);
	
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
