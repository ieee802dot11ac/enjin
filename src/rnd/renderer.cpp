#include "renderer.h"
#include "types.h"
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
	for (IDrawable* draw : mDraws) delete draw;
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow); 
}

void Renderer::Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
	for (IDrawable* draw : mDraws) draw->Draw();
	glEnd();
	SDL_GL_SwapWindow(mWindow);
}

void Renderer::InitGL() {
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	const float DEG2RAD = acos(-1.0f) / 180;
	const float front = 0.1;
	const float back = 10;
	float tangent = tan(60.0/2 * DEG2RAD);    // tangent of half fovY
	float top = front * tangent;              // half height of near plane
	float right = top * (4.0/3.0);          // half width of near plane
	Matrix mtx(4,4);
	mtx.get_mut(0, 0) = front/right;
	mtx.get_mut(1, 1) = front/top;
	mtx.get_mut(2, 2) = -(back + front) / (back - front);
	mtx.get_mut(2, 3) = -1;
    mtx.get_mut(3, 2) = -(2 * back * front) / (back - front);
    mtx.get_mut(3, 3) =  0;
	glFrustum(-right, right, -top, top, front, back);
}
