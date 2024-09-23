/**
 * @file renderer.h
 * @author ieee 802.11ac
 * @brief SDL renderer class.
 * @version 0.1
 * @date 2024-09-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "interfaces/drawable.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <vector>

class Renderer {
public:
	Renderer();
	virtual ~Renderer();
	Renderer& operator=(const Renderer&) = delete;
	virtual void Draw();

	void push_back(IDrawable* draw) { mDraws.push_back(draw); }

	static void InitGL();

private:
	SDL_Window* mWindow;
	SDL_GLContext mContext;
	std::vector<IDrawable*> mDraws;
};
