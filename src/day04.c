#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum grid_value_t: char
{
	VALUE_INVALID = '\0',
	VALUE_PAPER   = '@',
	VALUE_EMPTY   = '.',
} grid_value_t;

typedef struct grid_t
{
	grid_value_t *values;
	size_t size;
} grid_t;

static size_t grid_size(FILE *file) // Assume it's square
{
	char *line = nullptr;
	size_t len = 0;

	getline(&line, &len, file);
	const size_t line_len = strlen(line) - 1; // Newline

	free(line);
	return line_len;
}

grid_value_t grid_get(const grid_t *grid, const size_t x, const size_t y)
{
	if (x >= grid->size || y >= grid->size)
	{
		return VALUE_INVALID;
	}

	return grid->values[x + y * grid->size];
}

bool grid_set(const grid_t *grid, const size_t x, const size_t y, const grid_value_t value)
{
	if (x >= grid->size || y >= grid->size)
	{
		return false;
	}

	grid->values[x + (y * grid->size)] = value;
	return true;
}

static void grid_fill(const grid_t *grid, FILE *file)
{
	char *line = nullptr;
	size_t len = 0;

	size_t y = 0;
	while (getline(&line, &len, file) >= 0)
	{
		for (auto x = 0; x < grid->size; x++)
		{
			assert(grid_set(grid, x, y, line[x]));
		}
		y++;
	}
}

static int adjacent_count(const grid_t *grid, const int x, const int y, const grid_value_t value)
{
	auto count = 0;

	for (int ry = y - 1; ry <= y + 1; ry++)
	{
		for (int rx = x - 1; rx <= x + 1; rx++)
		{
			if (rx == x && ry == y)
			{
				continue;
			}

			if (grid_get(grid, rx, ry) == value)
			{
				count++;
			}
		}
	}

	return count;
}

int main()
{
	FILE *file = fopen("input/04", "r");

	grid_t grid;
	grid.size = grid_size(file);
	grid.values = malloc(sizeof(grid_value_t) * grid.size * grid.size);

	fseek(file, 0, SEEK_SET);
	grid_fill(&grid, file);

	auto rolls = 0;

	for (auto y = 0; y < grid.size; y++)
	{
		for (auto x = 0; x < grid.size; x++)
		{
			if (grid_get(&grid, x, y) != VALUE_PAPER)
			{
				continue;
			}

			if (adjacent_count(&grid, x, y, VALUE_PAPER) < 4)
			{
				rolls++;
			}
		}
	}

	printf("paper rolls: %d\n", rolls);

	fclose(file);
	free(grid.values);
	return 0;
}
