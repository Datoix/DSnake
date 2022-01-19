#pragma once

#include "game.h"

struct Cell {
	struct Cell* parent;
	struct Cell* next;
	struct Coord coord;
};

struct Snake {
	struct Cell* head;
	struct Cell* back;
	int length;
};

void insert_front(struct Snake* snake, struct Coord coord);
void remove_back(struct Snake* snake);
int exists(struct Snake* snake, struct Coord coord);
int get_length(struct Snake* snake);