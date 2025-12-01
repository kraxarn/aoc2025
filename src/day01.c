#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *file = fopen("input/01", "r");

	auto password = 0;
	auto current = 50L;

	char *line = nullptr;
	size_t len;

	while (getline(&line, &len, file) != -1)
	{
		char *end;
		const long count = strtol(line + 1, &end, 10);

		switch (line[0])
		{
			case 'L':
				current -= count;
				break;

			case 'R':
				current += count;
				break;
		}

		while (current < 0)
		{
			current += 100;
		}

		while (current > 99)
		{
			current -= 100;
		}

		if (current == 0)
		{
			password++;
		}
	}

	printf("password: %d\n", password);

	free(line);
	fclose(file);
	return 0;
}
