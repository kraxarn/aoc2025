#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *file = fopen("input/02", "r");

	char *line = nullptr;
	size_t len;
	getline(&line, &len, file);

	auto result = 0L;

	const char *current = line;
	while (current != nullptr)
	{
		char *end = strchr(current, ',');

		char *split = nullptr;
		const long range_start = strtol(current, &split, 10);
		const long range_end = strtol(split + 1, &split, 10);

		for (auto i = range_start; i <= range_end; i++)
		{
			char *str;
			const int str_len = asprintf(&str, "%ld", i);
			if (str_len % 2 != 0)
			{
				continue;
			}

			char *str1 = malloc((str_len / 2) + 1);
			strlcpy(str1, str, (str_len / 2) + 1);

			char *str2 = malloc((str_len / 2) + 1);
			strlcpy(str2, str + (str_len / 2), (str_len / 2) + 1);

			if (strcmp(str1, str2) == 0)
			{
				result += i;
			}

			free(str);
			free(str1);
			free(str2);
		}

		current = end != nullptr ? end + 1 : end;
	}

	printf("sum: %ld\n", result);

	free(line);
	fclose(file);
	return 0;
}
