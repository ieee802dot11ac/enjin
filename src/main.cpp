#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "rnd/mesh.h"
#include "rnd/renderer.h"
#include "serial/stream.h"
#include <iostream>
#include <stdint.h>

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_EVERYTHING);
	Renderer* rnd = new Renderer;
	SDL_Event e; bool quit = false;
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glDisable(GL_CULL_FACE);
	Mesh* mesh = new Mesh;
	{
		FileStream fs("test2.xpmf", true);
		mesh->Load(fs);
	}
	rnd->push_back(mesh); 
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
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_UP) {
					for (Vertex& v : mesh->mVerts) {
						v.col += 0.1f;
					}
				} else if (e.key.keysym.sym == SDLK_DOWN) {
					for (Vertex& v : mesh->mVerts) {
						v.col -= 0.1f;
					}
				}
			}
    	}
		rnd->Draw();
	}
	delete rnd;
	SDL_Quit();
	return 0;
}
