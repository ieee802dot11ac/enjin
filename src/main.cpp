#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_opengl.h>
#include "rnd/mesh.h"
#include "rnd/renderer.h"
#include "serial/stream.h"
#include <iostream>
#include <stdint.h>

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_EVERYTHING);

	Renderer* rnd = new Renderer;
	Renderer::InitGL();

	Mesh* mesh = new Mesh;
	{
		FileStream fs("test2.xpmf", true);
		mesh->Load(fs);
	}
	rnd->push_back(mesh); 

	SDL_Event e; bool quit = false;
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
						v.pos.flt[2] += 0.1f;
					}
				} else if (e.key.keysym.sym == SDLK_DOWN) {
					for (Vertex& v : mesh->mVerts) {
						v.pos.flt[2] -= 0.1f;
					}
				}
				if (e.key.keysym.sym == SDLK_LEFT) {
					for (Vertex& v : mesh->mVerts) {
						v.pos.flt[0] -= 0.1f;
					}
				} else if (e.key.keysym.sym == SDLK_RIGHT) {
					for (Vertex& v : mesh->mVerts) {
						v.pos.flt[0] += 0.1f;
					}
				}
				if (e.key.keysym.sym == SDLK_SPACE) {
					mesh->mVerts[0].col.flt[0] = 1.0f;
					mesh->mVerts[0].col.flt[1] = 0.0f;
					mesh->mVerts[0].col.flt[2] = 0.0f;

					mesh->mVerts[1].col.flt[0] = 0.0f;
					mesh->mVerts[1].col.flt[1] = 1.0f;
					mesh->mVerts[1].col.flt[2] = 0.0f;

					mesh->mVerts[2].col.flt[0] = 0.0f;
					mesh->mVerts[2].col.flt[1] = 0.0f;
					mesh->mVerts[2].col.flt[2] = 1.0f;
				}
			}
    	}
		rnd->Draw();
	}
	delete rnd;
	SDL_Quit();
	return 0;
}
