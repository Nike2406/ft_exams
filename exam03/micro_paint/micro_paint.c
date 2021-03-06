#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int		width, height;
float	x, y, w, h;
char	*draw;
char	type, back, color;

int	check_hit(float i, float j)
{
	if (i < x || x + w < i || j < y || y + h < j)
		return (0);
	if (i - x < 1 || x + w - i < 1 || j - y < 1 || y + h - j < 1)
		return (2);
	return (1);
}

void	drawing(void)
{
	int	i, j, hit;

	i = -1;
	while (++i < width)
	{
		j = -1;
		while (++j < height)
		{
			hit = check_hit((float)i, (float)j);
			if (hit == 2 || (hit == 1 && type == 'R'))
				draw[i + j * width] = color;
		}
	}
}

int	parser(FILE *file)
{
	int	i, res;

	i = 0;
	if (fscanf(file, "%d %d %c\n", &width, &height, &back) != 3)
		return (1);
	if (width < 1 || width > 300 || height < 1 || height > 300)
		return (1);
	draw = malloc(width * height);
	if (draw == NULL)
		return (1);
	while (i < width * height)
		draw[i++] = back;
	while ((res = fscanf(file, "%c %f %f %f %f %c\n", &type, &x, &y, &w, &h, &color)) == 6)
	{
		if (w <= 0 || h <= 0 || (type != 'R' && type != 'r'))
			return (1);
		drawing();
	}
	if (res != -1)
		return (1);
	return (0);
}

void	output(void)
{
	int i = -1;
	while (++i < height)
	{
		write(1, draw + i * width, width);
		write(1, "\n", 1);
	}
}

int		main(int ac, char **av)
{
	FILE	*file;
	if (ac != 2)
	{
		write(1, "Error: argumnet\n", 16);
		return (1);
	}
	if (!(file = fopen(av[1], "r")) || parser(file))
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	output();
	fclose(file);
	free(draw);
	return (0);
}

