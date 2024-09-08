#include "renderer.h"
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_video.h>

Renderer::Renderer() { 
    mWindow = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_assert(mWindow != NULL);
    mContext = SDL_GL_CreateContext(mWindow);
    glViewport(0, 0, 800, 600);
    SDL_ShowWindow(mWindow);
}

Renderer::~Renderer() {
    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mWindow); 
}

void Renderer::Draw(std::vector<Vector3> verts) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	for (Vector3 vert : verts) {
        glVertex3fv(vert); // :3
    }
	glEnd();
	SDL_GL_SwapWindow(mWindow);
}
