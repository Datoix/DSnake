#include "snake.h"

void insert_front(struct Snake* snake, struct Coord coord) {
	struct Cell* cell = (struct Cell*)malloc(sizeof(struct Cell));
	cell->coord = coord;
	cell->next = snake->head;
	cell->parent = NULL;
	
	snake->head->parent = cell;
	snake->head = cell;
}

void remove_back(struct Snake* snake) {
	struct Cell* cell = snake->back;
	snake->back = cell->parent;
	cell->parent->next = NULL;
	free(cell);
}

int exists(struct Snake* snake, struct Coord coord) {
	struct Cell* cell = snake->head;

	while (cell != NULL) {
		if (cell->coord.x == coord.x && cell->coord.y == coord.y)
			return 1;

		cell = cell->next;
	}

	return 0;
}

int get_length(struct Snake* snake) {
	int c = 0;
	struct Cell* cell = snake->head;

	while (cell != NULL) {
		++c;
		cell = cell->next;
	}

	return c;
}
