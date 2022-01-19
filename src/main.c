#include "game.h"

const int FPS = 10; // constant snake speed

const int WIDTH = 700;
const int HEIGHT = 700;
const int ROWS = 20;
const int COLS = 20;

int main(void) {
	srand(time(0));
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow(
		"DSnake",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH,
		HEIGHT,
		0
	);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	struct Game* game = init_game(WIDTH, HEIGHT, ROWS, COLS);

	generate_food(game);

	int delay = 1000 / FPS;
	Uint32 start;
	int time;

	while (game->running) {
		start = SDL_GetTicks();

		handle_events(game); // change direction
		update(game); // snake movement
		draw(renderer, game); // snake draw

		time = SDL_GetTicks() - start;

		if (delay > time)
			SDL_Delay(delay - time);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}
