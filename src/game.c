#include "game.h"
#include "snake.h"

const struct Color BG_COLOR = { 0, 0, 0, 255 };
const struct Color BODY_COLOR = { 0, 0, 255, 255 };
const struct Color HEAD_COLOR = { 0, 0, 100, 255 };
const struct Color MISTAKE_COLOR = { 255, 0, 0, 255 };
const struct Color FOOD_COLOR = { 0, 255, 0, 255 };

struct Game* init_game(int width, int height, int rows, int cols) {
	struct Game* game = (struct Game*)malloc(sizeof(struct Game));
	
	game->rows = rows;
	game->cols = cols;
	game->row_size = height / rows;
	game->col_size = width / cols;
	game->direction = Right;
	game->running = 1;

	struct Cell* head = (struct Cell*)malloc(sizeof(struct Cell));
	head->coord.x = cols / 2;
	head->coord.y = rows / 2;
	head->next = NULL;
	head->parent = NULL;

	struct Snake* snake = (struct Snake*)malloc(sizeof(struct Snake));
	snake->head = head;
	snake->back = head;
	snake->length = 1;

	game->snake = snake;

	return game;
}

void handle_events(struct Game* game) {
	SDL_Event e;
	
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) game->running = 0;
		else if (e.type == SDL_KEYDOWN)
			// arrow control
			switch (e.key.keysym.sym) {
				case SDLK_UP:
					if (game->direction != Down) game->direction = Up;
					break;
				case SDLK_DOWN:
					if (game->direction != Up) game->direction = Down;
					break;
				case SDLK_LEFT:
					if (game->direction != Right) game->direction = Left;
					break;
				case SDLK_RIGHT:
					if (game->direction != Left) game->direction = Right;
					break;
			}
	}
}

void update(struct Game* game) {
	struct Coord move;
	move.x = 0;
	move.y = 0;

	switch (game->direction) {
		case Up:
			--move.y;
			break;
		case Down:
			++move.y;
			break;
		case Left:
			--move.x;
			break;
		case Right:
			++move.x;
			break;
	}

	int new_x = game->snake->head->coord.x + move.x;
	int new_y = game->snake->head->coord.y + move.y;
	
	// set new position

	if (new_x < 0) new_x = game->rows - 1;
	if (new_x >= game->rows) new_x = 0;
	if (new_y < 0) new_y = game->cols - 1;
	if (new_y >= game->cols) new_y = 0;
	
	// teleport snake if its outside borders

	struct Coord coord;
	coord.x = new_x;
	coord.y = new_y;

	if (exists(game->snake, coord)) { // if head touching tail
		game->running = 0;
		return;
	}

	insert_front(game->snake, coord); // add to front

	if (game->food.x == new_x && game->food.y == new_y) { // if touching food
		++game->snake->length; // increase length
		generate_food(game); // create new food
	} else if (get_length(game->snake) > game->snake->length) {
		remove_back(game->snake); // remove excess cell
	}
}

void draw(SDL_Renderer* renderer, struct Game* game) {
	SDL_SetRenderDrawColor(renderer, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a);
	SDL_RenderClear(renderer);

	SDL_Rect rect;
	rect.w = game->col_size - 2;
	rect.h = game->row_size - 2;

	// draw head in different color
	SDL_SetRenderDrawColor(renderer, HEAD_COLOR.r, HEAD_COLOR.g, HEAD_COLOR.b, HEAD_COLOR.a);
	rect.x = game->snake->head->coord.x * game->col_size + 1;
	rect.y = game->snake->head->coord.y * game->row_size + 1;

	SDL_RenderFillRect(renderer, &rect);

	struct Cell* cell = game->snake->head->next;

	// draw tail
	while (cell != NULL) {
		rect.x = cell->coord.x * game->col_size + 1;
		rect.y = cell->coord.y * game->row_size + 1;

		SDL_SetRenderDrawColor(renderer, BODY_COLOR.r, BODY_COLOR.g, BODY_COLOR.b, BODY_COLOR.a);
		SDL_RenderFillRect(renderer, &rect);
		cell = cell->next;
	}
		
	// draw food
	SDL_SetRenderDrawColor(renderer, FOOD_COLOR.r, FOOD_COLOR.g, FOOD_COLOR.b, FOOD_COLOR.a);
	rect.x = game->food.x * game->col_size + 5;
	rect.y = game->food.y * game->row_size + 5;
	rect.w -= 10;
	rect.h -= 10;

	SDL_RenderFillRect(renderer, &rect);

	SDL_RenderPresent(renderer);
}

void generate_food(struct Game* game) {
	int x = rand() % game->rows;
	int y = rand() % game->cols;

	game->food.x = x;
	game->food.y = y;
}