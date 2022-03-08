#include "Engine.h"

#pragma region ECS
Entity::Entity()
{
	transform = addComponent<Transform>();
	renderer = addComponent<Renderer>();
}

Entity::~Entity() {}

void Entity::destroy()
{
	active = false;
}

void Entity::update()
{
	for (Component* c : components)
	{
		c->update();
	}
}

void Entity::render()
{
	for (Component* c : components)
	{
		c->render();
	}
}

void Entity::log()
{
	std::cout << "Position: ";
	transform->position.print();
}

template <typename T>
T* Entity::addComponent()
{
	T* newComponent = new T();
	newComponent->owner = this;
	components.push_back(newComponent);
	return newComponent;
}

template <typename T>
T* Entity::getComponent()
{
	for (Component* component : components)
	{
		if (typeid(*component).name() == typeid(T).name())
		{
			return (T*)component;
		}
	}
}

Component::~Component() {}
void Component::start() {}
void Component::update() {}
void Component::render() {}
#pragma endregion

#pragma region Components
Transform::~Transform() {}
Transform::Transform()
{
	position = Vector2(0, 0);
	scale = Vector2(32, 32);
}
void Transform::update(){}

Renderer::~Renderer(){}
Renderer::Renderer()
{
	color = Color::White;
}

void Renderer::render()
{
	SDL_SetRenderDrawColor(owner->sdl_renderer, color.r, color.g, color.b, color.a);
	SDL_Rect rect = 
	{
		owner->transform->position.x, 
		owner->transform->position.y, 
		owner->transform->scale.x, 
		owner->transform->scale.y 
	};
	SDL_RenderFillRect(owner->sdl_renderer, &rect);
}
#pragma endregion

#pragma region Engine
Engine::Engine() {}

Engine::~Engine() {}

void Engine::init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
	// successfully initialized SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		printf("Engine init\n");
		window = new Window(title, x, y, width, height, fullscreen);
		renderer = SDL_CreateRenderer(window->sdl_window, -1, 0);
		input = new Input();
		time = new Time();
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
}

void Engine::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
			{
				isRunning = false;
				break;
			}
			case SDL_KEYDOWN:
			{
				int scancode = event.key.keysym.scancode;
				input->keys[scancode] = true;
				break;
			}
			case SDL_KEYUP:
			{
				int scancode = event.key.keysym.scancode;
				input->keys[scancode] = false;
				break;
			}
		}
	}
}

 Entity* entity = nullptr;

void Engine::start() 
{
	// Creating entity
	entity = new Entity();
	addEntity(entity);
}

void Engine::update()
{
	for (Entity* entity : entities)
	{
		entity->update();
	}
}

void Engine::render()
{
	SDL_SetRenderDrawColor(renderer, 25, 25, 40, 255);
	SDL_RenderClear(renderer);

	for (Entity* entity : entities)
	{
		entity->render();
	}

	SDL_RenderPresent(renderer);
}

void Engine::clean()
{
	SDL_DestroyWindow(window->sdl_window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Engine cleaned");
}
#pragma endregion

#pragma region Input
Input::Input() {}
Input::~Input() {}

bool Input::GetKeyDown(int scancode)
{
	return keys[scancode] == true;
}

bool Input::GetKeyUp(int scancode)
{
	return keys[scancode] == false;
}
#pragma endregion

#pragma region Time
Time::Time() {}
Time::~Time() {}
#pragma endregion