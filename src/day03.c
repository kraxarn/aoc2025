#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *file = fopen("input/03", "r");

	auto rating = 0L;

	char *line = nullptr;
	size_t len;

	while (getline(&line, &len, file) != -1)
	{
		const size_t line_len = strlen(line) - 1; // Newline
		auto max = 0L;

		for (size_t i = 0; i < line_len; i++)
		{
			for (size_t j = i + 1; j < line_len; j++)
			{
				const char temp[3] = {line[i], line[j], '\0'};
				const long value = strtol(temp, nullptr, 10);
				max = max > value ? max : value;
			}
		}

		rating += max;
	}

	printf("rating: %ld\n", rating);

	free(line);
	fclose(file);
	return 0;
}
