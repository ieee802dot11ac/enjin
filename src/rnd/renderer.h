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

#include "math/vec.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <vector>

class Renderer {
public:
	Renderer();
	virtual ~Renderer();
	Renderer& operator=(const Renderer&) = delete;
	virtual void Draw(std::vector<Vector3> verts);
	SDL_Window* mWindow;
private:
	SDL_GLContext mContext;
};
