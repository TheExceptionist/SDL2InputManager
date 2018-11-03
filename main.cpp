#include <iostream>
#include <SDL2/SDL.h>

enum
{
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,

	KEY_NUM
};

bool running = true;

SDL_Window* window;
SDL_Surface* surface;

int p_x = 0, p_y = 0;

void move(const int x, const int y)
{
	p_x += x;
	p_y += y;
	printf("New Pos: (%d, %d)\n", p_x, p_y);
}

class KeyBinding
{
public:
	virtual ~KeyBinding() {}
	virtual void execute() = 0;
};

class MoveKeys : public KeyBinding
{
public:
	MoveKeys(const int x, const int y) : m_x(x), m_y(y) {}
	virtual void execute() { move(m_x, m_y); }
protected:
	int m_x, m_y;
};

class InputManager
{
public:
	InputManager();
	virtual ~InputManager();

	static InputManager& get() 
	{
		static InputManager* manager = new InputManager();
		return *manager;
	}

	KeyBinding& getKey(const int code)
	{
		switch(code)
		{
			case KEY_RIGHT:
			{
				return *right;
			} 
			case KEY_LEFT:
			{
				return *left;
			} 
			case KEY_UP:
			{
				return *up;
			} 
			case KEY_DOWN:
			{
				return *down;
			} 
		}
	}

private:
	KeyBinding* left;
	KeyBinding* right;
	KeyBinding* up;
	KeyBinding* down;

};

InputManager::InputManager()
{
	left = new MoveKeys(-1, 0);
	right = new MoveKeys(1, 0);
	up = new MoveKeys(0, -1);
	down = new MoveKeys(0, 1);
}

InputManager::~InputManager()
{
	delete left;
	delete right;
	delete up; 
	delete down;
}

void close()
{
	SDL_FreeSurface(surface);
	surface = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();

	running = false;
}

int main()
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Could not initialize video!");
	}
	else
	{
		window = SDL_CreateWindow("SDLKeys Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

		if(window == NULL)
		{
			printf("Could not initialize window!");
		}
		else
		{
			surface = SDL_GetWindowSurface(window);

			if(surface == NULL)
			{
				printf("Could not initialize surface!");
			}
		}
	}

	while(running)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
				{
					close();
				}break;
				case SDL_KEYDOWN:
				{
					switch(event.key.keysym.sym)
					{
						case SDLK_LEFT:
						{
							printf("Left\n");
							InputManager::get().getKey(KEY_LEFT).execute();
						} break;
						case SDLK_RIGHT:
						{
							printf("Right\n");
							InputManager::get().getKey(KEY_RIGHT).execute();
						} break;
						case SDLK_UP:
						{
							printf("Up\n");
							InputManager::get().getKey(KEY_UP).execute();
						} break;
						case SDLK_DOWN:
						{
							printf("Down\n");
							InputManager::get().getKey(KEY_DOWN).execute();
						} break;
						default:
						{
							printf("Pressed\n");
						} break;
					}
				} break;
			}
		}
	}

	return 0;
}
