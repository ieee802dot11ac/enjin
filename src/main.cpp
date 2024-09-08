#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "rnd/mesh.h"
#include "rnd/renderer.h"
#include <iostream>
#include <stdint.h>

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_EVERYTHING);
	Renderer* rnd = new Renderer;
	SDL_Event e; bool quit = false;
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glDisable(GL_CULL_FACE);
	auto mesh = load_mesh("test.mesh");
	while (!quit) {
		const char* err = SDL_GetError();
		int gl_err = glGetError();
		if (strcmp(err, "") || gl_err != 0) {
			std::cerr << "oh fuck! SDL error: " << err << std::endl;
			std::cerr << "GL error: " << gl_err << std::endl;
			exit(420);
		}
    	while (SDL_PollEvent(&e)) {
        	if (e.type == SDL_QUIT){
        	    quit = true;
        	}
    	}
		rnd->Draw(mesh);
	}
	delete rnd;
	SDL_Quit();
	return 0;
}
