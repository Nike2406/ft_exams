#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_drawing
{
	char	*canvas;
	int		width;
	int		height;
	char	background;
}	t_drawing;

typedef struct s_rectangle
{
	char	type;
	float	rec_x;
	float	rec_y;
	float	rec_w;
	float	rec_h;
	char	color;
}	t_rectangle;

FILE		*file;
t_drawing	d;
t_rectangle	r;

int	get_info(void)
{
	if (fscanf(file, "%d %d %c\n", &d.width, &d.height, &d.background) != 3)
		return (0);
	if (d.width < 1 || d.width > 300 || d.height < 1 || d.height > 300)
		return (0);
	if (!(d.canvas = malloc(d.height * d.width)))
		return (0);
	memset(d.canvas, d.background, d.height * d.width);
	return (1);
}

int	in_rectangle(float x, float y)
{
	if (x < r.rec_x || r.rec_x + r.rec_w < x || y < r.rec_y || r.rec_y + r.rec_h < y)
		return (0);
	if (x - r.rec_x < 1 || (r.rec_x + r.rec_w) - x < 1 ||
		y - r.rec_y < 1 || (r.rec_y + r.rec_h) - y < 1)
		return (2);
	return (1);
}

int	apply(void)
{
	int	x, y, is;

	if((r.rec_w <= 0 || r.rec_h <= 0) || (r.type != 'R' && r.type != 'r'))
		return (0);
	x = -1;
	while (++x < d.width)
	{
		y = -1;
		while (++y < d.height)
			if ((is = in_rectangle(x, y)) == 2 || (is == 1 && r.type == 'R'))
				d.canvas[x + y * d.width] = r.color;
	}
	return (1);
}

int	exec(void)
{
	int	x;
	int	scan;

	x = -1;
	if (!get_info())
		return (0);
	while ((scan = fscanf(file, "%c %f %f %f %f %c\n", &r.type, &r.rec_x, &r.rec_y, &r.rec_w, &r.rec_h, &r.color)) == 6)
		if (!apply())
			return (0);
	if (scan != -1)
		return (0);
	while (++x < d.height)
		write(1, d.canvas + (x * d.width), d.width) && write (1, "\n",1);
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		file = fopen(argv[1], "r");
		if (file && exec())
			return (0);
		write (1, "Error: Operation file corrupted\n", 32);
	}
	else
		write(1, "Error: argument\n", 16);
	return (1);
}
