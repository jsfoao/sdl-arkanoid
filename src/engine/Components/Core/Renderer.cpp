#include "Renderer.h"
#include "Transform.h"

Renderer::~Renderer() {}
Renderer::Renderer()
{
	color = Color::White;
}

void Renderer::render()
{
	SDL_SetRenderDrawColor(owner->sdl_renderer, color.r, color.g, color.b, color.a);
	SDL_Rect rect =
	{
		owner->transform->position.x - (owner->transform->scale.x / 2),
		owner->transform->position.y - (owner->transform->scale.y / 2),
		owner->transform->scale.x,
		owner->transform->scale.y
	};
	SDL_RenderFillRect(owner->sdl_renderer, &rect);
}