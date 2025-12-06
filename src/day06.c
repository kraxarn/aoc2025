#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static long solve(const char *line, const long *nums, const size_t nums_size)
{
	char *ops = malloc(strlen(line));
	size_t ops_i = 0;
	for (size_t i = 0; i < strlen(line); i++)
	{
		if (line[i] == '+' || line[i] == '*')
		{
			ops[ops_i++] = line[i];
		}
	}
	ops[ops_i] = '\0';
	const size_t ops_size = strlen(ops);

	long result = 0;

	for (size_t i = 0; i < ops_size; i++)
	{
		long temp = 0;
		const char op = ops[i];

		for (size_t j = i; j < nums_size; j += ops_size)
		{
			if (temp == 0)
			{
				temp = nums[j];
				continue;
			}

			switch (op)
			{
				case '+':
					temp += nums[j];
					break;

				case '*':
					temp *= nums[j];
					break;
			}
		}

		result += temp;
	}

	free(ops);
	return result;
}

int main()
{
	FILE *file = fopen("input/06", "r");

	char *line = nullptr;
	size_t len;

	long *nums = nullptr;
	size_t nums_size = 0;

	long result = 0;

	while (getline(&line, &len, file) >= 0)
	{
		char *current = line;
		while (*current != '\n')
		{
			const long value = strtol(current, &current, 10);
			if (value == 0)
			{
				result = solve(line, nums, nums_size);
				break;
			}

			nums = realloc(nums, sizeof(long) * (nums_size + 1));
			nums[nums_size] = value;
			nums_size++;
		}
	}

	printf("total: %ld\n", result);

	free(nums);
	free(line);
	fclose(file);
	return 0;
}
