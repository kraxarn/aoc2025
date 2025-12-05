#include <stdio.h>
#include <stdlib.h>

typedef struct range_t
{
	long start;
	long end;
} range_t;

static bool in_range(const range_t *range, const long value)
{
	return value >= range->start && value <= range->end;
}

int main()
{
	FILE *file = fopen("input/05", "r");

	char *line = nullptr;
	size_t len;

	auto fresh = 0L;

	range_t **ranges = nullptr;
	size_t range_size = 0;

	while (getline(&line, &len, file) >= 0)
	{
		if (line[0] == '\n')
		{
			break;
		}

		range_t *range = malloc(sizeof(range_t));

		char *end = nullptr;
		range->start = strtol(line, &end, 10);
		range->end = strtol(end + 1, &end, 10);

		ranges = realloc(ranges, sizeof(range_t) * (range_size + 1));
		ranges[range_size++] = range;
	}

	while (getline(&line, &len, file) >= 0)
	{
		char *end = nullptr;
		const long value = strtol(line, &end, 10);

		for (size_t i = 0; i < range_size; i++)
		{
			if (in_range(ranges[i], value))
			{
				fresh++;
				break;
			}
		}
	}

	printf("fresh: %ld\n", fresh);

	for (size_t i = 0; i < range_size; i++)
	{
		free(ranges[i]);
	}
	free(ranges);

	free(line);
	fclose(file);
	return 0;
}
