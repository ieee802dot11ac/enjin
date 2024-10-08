#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_opengl.h>
#include "rnd/mesh.h"
#include "rnd/renderer.h"
#include <iostream>
#include <stdint.h>

#define OBJNAME "/tmp/neut.obj"

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_EVERYTHING);
	Texture::Init();

	Renderer* rnd = new Renderer;
	Renderer::InitGL();

	Mesh* mesh = new Mesh;
	{
		std::ifstream fs; fs.open(OBJNAME);
		mesh->ImportOBJ(fs);
		fs.close();		
	}
	rnd->push_back(mesh); 

	SDL_Event e; bool quit = false;
	while (!quit) {
		const char* err = SDL_GetError(); bool sdl_err = strcmp(err, "");
		int gl_err = glGetError();
		if (sdl_err || gl_err != 0) {
			std::cerr << "oh fuck!" << std::endl;
			if (sdl_err) std::cerr << "SDL error: " << err << std::endl;
			if (gl_err) std::cerr << "GL error: " << gl_err << std::endl;
			exit(420);
		}
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT){
				quit = true;
			}
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_UP) {
					for (Vertex& v : mesh->mVerts) {
						v.pos.y -= 0.1f;
					}
				} else if (e.key.keysym.sym == SDLK_DOWN) {
					for (Vertex& v : mesh->mVerts) {
						v.pos.y += 0.1f;
					}
				}
				if (e.key.keysym.sym == SDLK_LEFT) {
					for (Vertex& v : mesh->mVerts) {
						v.pos.x += 0.1f;
					}
				} else if (e.key.keysym.sym == SDLK_RIGHT) {
					for (Vertex& v : mesh->mVerts) {
						v.pos.x -= 0.1f;
					}
				}
				if (e.key.keysym.sym == SDLK_SPACE) {
					mesh->mVerts[0].col.x = 1.0f;
					mesh->mVerts[0].col.y = 0.0f;
					mesh->mVerts[0].col.z = 0.0f;

					mesh->mVerts[1].col.x = 0.0f;
					mesh->mVerts[1].col.y = 1.0f;
					mesh->mVerts[1].col.z = 0.0f;

					mesh->mVerts[2].col.x = 0.0f;
					mesh->mVerts[2].col.y = 0.0f;
					mesh->mVerts[2].col.z = 1.0f;

					mesh->mVerts[3].col.w = 0.33f;
				}
				if (e.key.keysym.sym == SDLK_RETURN) {
					rnd->pop_back();
					std::ifstream fs; fs.open(OBJNAME);
					mesh->mVerts.clear();
					mesh->mFaces.clear();
					mesh->ImportOBJ(fs);
					fs.close();
					rnd->push_back(mesh);
				}
				if (e.key.keysym.sym == SDLK_ESCAPE) {
					Mesh::sWireframe = !Mesh::sWireframe;
				}
			}
		}
		rnd->Draw();
	}
	delete rnd;
	SDL_Quit();
	return 0;
}
