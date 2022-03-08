#include "Engine.h"

Engine* n_engine = nullptr;

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
	if (!active){ return;}

	for (Component* c : components)
	{
		c->update();
	}
}

void Entity::render()
{
	if (!active) { return; }

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
#pragma region Transform
Transform::~Transform() {}
Transform::Transform()
{
	position = Vector2(0, 0);
	scale = Vector2(32, 32);
}
void Transform::update() {}
#pragma endregion

#pragma region Renderer
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
#pragma endregion

#pragma region PlayerController
PlayerController::PlayerController()
{
	speed = 200;
}

void PlayerController::update()
{
	if (n_engine->input->GetKeyDown(SDL_SCANCODE_W))
	{
		owner->transform->position.y -= speed * n_engine->time->deltaTime;
	}
	if (n_engine->input->GetKeyDown(SDL_SCANCODE_S))
	{
		owner->transform->position.y += speed * n_engine->time->deltaTime;
	}
	if (n_engine->input->GetKeyDown(SDL_SCANCODE_A))
	{
		owner->transform->position.x -= speed * n_engine->time->deltaTime;
	}
	if (n_engine->input->GetKeyDown(SDL_SCANCODE_D))
	{
		owner->transform->position.x += speed * n_engine->time->deltaTime;
	}
}
#pragma endregion

#pragma region BoxCollider
BoxCollider::BoxCollider()
{
	color = Color::White;
	scale = Vector2(32, 32);
}
void BoxCollider::update()
{
	position = owner->transform->position + offset;
}
void BoxCollider::render()
{
	SDL_SetRenderDrawColor(owner->sdl_renderer, color.r, color.g, color.b, color.a);
	SDL_Rect rect =
	{
		position.x - (scale.x / 2),
		position.y - (scale.y / 2),
		scale.x,
		scale.y
	};

	SDL_RenderDrawRect(owner->sdl_renderer, &rect);
}
bool aabb_intersect(const BoxCollider* a, const BoxCollider* b)
{
	return 
		(
		a->position.x < b->position.x + b->scale.x &&
		a->position.x + a->scale.x > b->position.x &&
		a->position.y < b->position.y + b->scale.y &&
		a->position.y + a->scale.y > b->position.y
		);
}
#pragma endregion

#pragma region CircleCollider
CircleCollider::CircleCollider()
{
	radius = 32;
}
void CircleCollider::update()
{
	position = owner->transform->position + offset;
}

const float PI = 3.1415;

void CircleCollider::render()
{
	int resolution = 32;
	float step = (2 * PI) / resolution;

	for (int i = 0; i < resolution; ++i)
	{
		float angle = step * i;
		float x1 = cos(angle);
		float y1 = sin(angle);

		float next_angle = step * (i + 1);
		float x2 = cos(next_angle);
		float y2 = sin(next_angle);

		SDL_RenderDrawLine(
			owner->sdl_renderer,
			x1 * radius + position.x,
			y1 * radius + position.y,
			x2 * radius + position.x,
			y2 * radius + position.y
		);
	}
}

bool circle_intersect(const CircleCollider* a, const CircleCollider* b)
{
	int dx = b->position.x - a->position.x;
	int dy = b->position.y - a->position.y;

	int dist_sqrd = dx * dx + dy * dy;
	int dist = sqrt(dist_sqrd);

	int radius_sum = a->radius + b->radius;
	return dist < radius_sum;
}

int clamp(int a, int min, int max)
{
	if (a < min)
		return min;
	if (a > max)
		return max;

	return a;
}

bool aabb_circle_intersect(const BoxCollider* box, const CircleCollider* circle)
{
	float xMin = box->position.x - (box->scale.x / 2);
	float xMax = box->position.x + (box->scale.x / 2);
	float yMin = box->position.y - (box->scale.y / 2);
	float yMax = box->position.y + (box->scale.y / 2);

	float clamped_x = clamp(circle->position.x, xMin, xMax);
	float clamped_y = clamp(circle->position.y, yMin, yMax);

	float dx = circle->position.x - clamped_x;
	float dy = circle->position.y - clamped_y;

	float dist_sqrd = dx * dx + dy * dy;
	float dist = sqrt(dist_sqrd);

	return dist < circle->radius;
}
#pragma endregion

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

// Entities
Entity* player = nullptr;
Entity* box = nullptr;

void Engine::start() 
{
	// Player entity
	player = new Entity();
	player->addComponent<PlayerController>();
	player->addComponent<BoxCollider>();
	player->getComponent<Renderer>()->color = Color::Blue;

	box = new Entity();
	box->addComponent<CircleCollider>();
	box->getComponent<Transform>()->position = Vector2(300, 300);
	box->getComponent<Renderer>()->color = Color::Red;

	addEntity(player);
	addEntity(box);
}

void Engine::update()
{
	for (Entity* entity : entities)
	{
		entity->update();
	}

	if (aabb_circle_intersect(player->getComponent<BoxCollider>(), box->getComponent<CircleCollider>()))
	{
		box->getComponent<Renderer>()->color = Color::Green;
	}
	else
	{
		box->getComponent<Renderer>()->color = Color::Red;
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