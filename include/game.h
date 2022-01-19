#pragma once

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

struct Color { Uint8 r, g, b, a; };
struct Coord { int x, y; };
enum Direction { Up, Down, Left, Right };

const struct Color BG_COLOR;
const struct Color BODY_COLOR;
const struct Color HEAD_COLOR;
const struct Color MISTAKE_COLOR;

struct Game {
	int rows, cols;
	int row_size, col_size;
	enum Direction direction;
	int running;

	struct Coord food;
	struct Snake* snake;
};

struct Game* init_game(int width, int height, int rows, int cols);

void handle_events(struct Game* game);
void update(struct Game* game);
void draw(SDL_Renderer* renderer, struct Game* game);

void generate_food(struct Game* game);